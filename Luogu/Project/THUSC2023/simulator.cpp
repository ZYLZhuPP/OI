#include<string>

#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<deque>
#include<fstream>
#include<vector>

using namespace std;

const bool SET_NEWLINE_AS_END = true;
const int MAX_SOURCE_LEN = 3e5;
const int GLOBAL_MAX_ID = 1e5;
typedef unsigned char Signal;
typedef unsigned int Index;

Index CaseNum, SimulateType, MaxID, ClockLoopTime, DFFMaximum, MaxTcomb,
    MaxDegree, InSignalNum, OutSignalNum;
vector<Index> InputPort, OutputPort;
ifstream in;
ofstream out, dbg;

void wrong(const char *str) {
  printf("\rError: %s.\n", str);
  exit(1);
}

#define verify(cl, err)    \
  {                        \
    if (!(cl)) wrong(err); \
  }

namespace Utils {
bool sort_by_size(vector<Index> &a, vector<Index> &b) {
  return a.size() < b.size();
}
// an easy way to optimize the process
vector<Index> merge_vectors(vector<vector<Index> > vecs) {
  sort(vecs.begin(), vecs.end(), sort_by_size);
  vector<Index> res(0), tmp(0);
  for (int i = 0; i < (int)vecs.size(); i++) {
    int p1 = 0, p2 = 0;
    tmp.clear();
    while (p1 != (int)vecs[i].size() && p2 != (int)res.size()) {
      if (vecs[i][p1] == res[p2]) {
        tmp.push_back(vecs[i][p1]);
        ++p1, ++p2;
      } else if (vecs[i][p1] > res[p2]) {
        tmp.push_back(res[p2++]);
      } else {
        tmp.push_back(vecs[i][p1++]);
      }
    }
    while (p1 != (int)vecs[i].size()) {
      tmp.push_back(vecs[i][p1++]);
    }
    while (p2 != (int)res.size()) {
      tmp.push_back(res[p2++]);
    }
    swap(res, tmp);
  }
  return res;
}
bool is_unique(vector<Index> vec) {
  sort(vec.begin(), vec.end());
  return unique(vec.begin(), vec.end()) == vec.end();
}
bool is_space(char ch) {
  return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}
string to_str(Index num) {
  if (num == 0) return "0";
  string ret = "";
  while (num) {
    ret += (char)('0' + (num % 10));
    num /= 10;
  }
  return string(ret.rbegin(), ret.rend());
}
}  // namespace Utils
using namespace Utils;

namespace StringView {
char str[MAX_SOURCE_LEN + 5];
int n;
void init() {
  char ch;
  while ((ch = getchar()) != EOF) {
    // ignore \r
    if (ch == '\r') continue;
    if (SET_NEWLINE_AS_END && ch == '\n' && (n == 0 || str[n - 1] == '\n'))
      break;
    str[n++] = ch;
    if (n > MAX_SOURCE_LEN) wrong("The input is too long");
  }
}
struct SRange {
  char *begin, *end;
  SRange() { begin = str, end = str + n; }
  SRange(char *begin, char *end) : begin(begin), end(end) {}
  bool empty() { return begin >= end; }
  char *find_next(char ch) {
    for (char *ptr = begin; ptr < end; ptr++)
      if (*ptr == ch) return ptr;
    return end;
  }
  char *find_next_plain(char ch) {
    int cur = 0;
    for (char *ptr = begin; ptr < end; ptr++) {
      if (*ptr == '(') ++cur;
      if (*ptr == ')' && --cur < 0) return end;
      if (*ptr == ch && cur == 0) return ptr;
    }
    return end;
  }
  void trim() {
    while (!empty() && is_space(*begin)) ++begin;
    while (!empty() && is_space(*(end - 1))) --end;
  }
  // use string for dynamic-length strings, for comparations and outputs
  string abstract() { return string(begin, end - begin); }
};

pair<Index, Index> getLoc(char *p) {
  pair<Index, Index> res(1, 0);
  for (char *ptr = str; ptr <= p; ptr++) {
    if (*ptr == '\n')
      res.first++, res.second = 0;
    else
      res.second++;
  }
  return res;
}
}  // namespace StringView
using StringView::SRange;

namespace SignalPool {
/*
  typeset:
    0 - 0
    1 - 1
    2 - X
*/
Signal mem[GLOBAL_MAX_ID + 10];
void init() {
  for (Index i = 1; i <= MaxID; i++) mem[i] = 2;
  mem[0] = 0;
}
// the function is unsafe, but the calls are
void write(Index idx, Signal val) { mem[idx] = val; }
Signal read(Index idx) { return mem[idx]; }
char readChar(Index idx) {
  if (mem[idx] == 2) return 'X';
  return '0' + mem[idx];
}
}  // namespace SignalPool

namespace Worker {
/*
  typeset:
    0 - SINGLE
    1 - NOR
    2 - XOR
    3 - NAND
    4 - AND
    5 - NXOR
    6 - OR
    7 - NOT
    8 - D_FF
*/
struct Unit {
  Signal type;
  Signal core;
  Signal storage;
  Index id;
  vector<Unit> children;
  Unit() {
    type = storage = id = 0;
    children.clear();
  }
  void push(Unit u) { children.push_back(u); }
  // the function is unsafe, but the calls are
  Signal operation(Signal a, Signal b) { return (core >> (a + b)) & 1; }
  bool check(Signal a) {
    return a ? core == 6 : core == 4;
  }
  Signal get() {
    if (type == 0) return SignalPool::read(id);
    if (type == 8) return storage;
    if (type == 7) {
      Signal res = SignalPool::read(children[0].id);
      return res == 2 ? 2 : !res;
    }
    Signal curr = 2;
    bool hasX = false;
    for (Index i = 0; i < children.size(); i++) {
      Signal res = children[i].get();
      if (res == 2)
        hasX = true;
      else if (curr == 2)
        curr = res;
      else
        curr = operation(curr, res);
    }
    if (curr == 2) return 2;
    if (hasX && !check(curr)) curr = 2;
    else if (type & 1)
      curr = !curr;
    return curr;
  }
  vector<Index> dependencies() {
    if (type == 0) return vector<Index>(1, id);
    if (type == 8) return vector<Index>(0);
    vector<vector<Index> > vecs;
    for (Index i = 0; i < children.size(); i++)
      vecs.push_back(children[i].dependencies());
    return merge_vectors(vecs);
  }
};

vector<pair<Index, Unit> > allUnits;

char *gen_errcode(SRange sr, const char *origin) {
  string res(origin);
  res = res + "\n- pos: ";
  if (sr.empty()) {
    pair<Index, Index> loc1 = StringView::getLoc(sr.begin);
    res = res + to_str(loc1.first) + ':' + to_str(loc1.second);
  } else {
    pair<Index, Index> loc1 = StringView::getLoc(sr.begin),
                       loc2 = StringView::getLoc(sr.end - 1);
    res = res + to_str(loc1.first) + ':' + to_str(loc1.second) + " ~ " +
          to_str(loc2.first) + ':' + to_str(loc2.second);
  }
  res += "\n- content: '" + sr.abstract() + "'";

  char *resp = new char[res.size() + 1];
  strcpy(resp, res.c_str());
  return resp;
}

bool get_index(SRange sr, Index &idx) {
  if (sr.empty()) return false;
  idx = 0;
  for (char *ptr = sr.begin; ptr != sr.end; ptr++) {
    if (*ptr > '9' || *ptr < '0') return false;
    idx = idx * 10 + (*ptr ^ '0');
  }
  return true;
}

Signal getType(SRange sr) {
  sr.trim();
  string s = sr.abstract();
  if (s == "NOR") return 1;
  if (s == "XOR") return 2;
  if (s == "NAND") return 3;
  if (s == "AND") return 4;
  if (s == "NXOR") return 5;
  if (s == "OR") return 6;
  if (s == "NOT") return 7;
  if (s == "D_FF") return 8;
  return 0;
}

Unit parseExp(SRange sr, short depth = 0) {
  sr.trim();
  if (sr.empty()) wrong(gen_errcode(sr, "The expression is empty"));

  Index tmp;
  Unit ret;
  if (get_index(sr, tmp)) {
    verify(tmp >= 0 && tmp <= MaxID, gen_errcode(sr, "Index out of range"));
    ret.id = tmp;
    return ret;
  }

  if (depth == 2) wrong(gen_errcode(sr, "Expected a single index"));

  char *brk = sr.find_next('(');
  if (brk != sr.end && *(sr.end - 1) == ')') {
    if ((ret.type = getType(SRange(sr.begin, brk))) == 0)
      wrong(gen_errcode(sr, "Invalid gate name"));
    if (depth == 1 && ret.type != 2 && ret.type != 4 && ret.type != 6)
      wrong(gen_errcode(
          sr, "The inner layer should only contain AND(), OR(), or XOR()"));
    if (SimulateType == 0 && ret.type == 8)
      wrong(gen_errcode(sr, "D_FF() should not exist"));
    if (ret.type == 8)
      ret.storage = 2;
    if (depth == 1 && ret.type == 8)
      wrong(gen_errcode(sr, "D_FF() should not be in the inner layer"));

    SRange inner(brk + 1, sr.end - 1);
    char *comma = brk;
    while (1) {
      comma = inner.find_next_plain(',');
      if (comma == inner.end) break;
      ret.children.push_back(parseExp(SRange(inner.begin, comma), depth + 1));
      inner.begin = comma + 1;
    }
    ret.children.push_back(parseExp(inner, depth + 1));

    if (ret.type >= 7 &&
        (ret.children.size() != 1 || ret.children[0].type != 0))
      wrong(gen_errcode(sr, "Unexpected parameters"));
    if (ret.children.size() > MaxDegree)
      wrong(gen_errcode(sr, "Number of parameters exceeds IN_SIGNAL_NUM"));
    // notice: all type should be the same
    Signal typeset = ret.children[0].type;
    for (unsigned int i = 1; i < ret.children.size(); i++) {
      if (typeset != ret.children[i].type)
        wrong(gen_errcode(sr, "The types of parameters should be the same"));
    }

    if (ret.type == typeset)
      wrong(gen_errcode(
          sr, "The type of parameters should differ from the caller"));

    if (ret.type & 1)
      ret.core = ret.type ^ 7;
    else
      ret.core = ret.type;

    return ret;
  }

  wrong(gen_errcode(sr, "Unknown expression"));
  return ret;
}

void parseSingle(SRange sr) {
  sr.trim();
  char *ptr = sr.find_next('=');
  verify(ptr != sr.end, gen_errcode(sr, "Expected equal sign"));
  Index tmp;

  SRange lhs(sr.begin, ptr);
  lhs.trim();
  verify(get_index(lhs, tmp), gen_errcode(lhs, "Not an index"));
  verify(tmp > 0 && tmp <= MaxID, gen_errcode(lhs, "Index out of range"));

  SRange rhs(ptr + 1, sr.end);
  rhs.trim();
  if (rhs.empty()) wrong(gen_errcode(sr, "The expression is empty"));

  allUnits.push_back(make_pair(tmp, parseExp(rhs)));
}

void parseCmd() {
  SRange sr;
  sr.trim();
  while (!sr.empty()) {
    char *ptr = sr.find_next(';');
    if (ptr == sr.end) wrong("Unexpected command after semicolon");
    parseSingle(SRange(sr.begin, ptr));
    sr.begin = ptr + 1;
  }
}

vector<Index> dffs;
vector<Index> topo;
vector<Index> degrees;
bool signalDegrees[GLOBAL_MAX_ID + 5];
vector<Index> relatedUnit[GLOBAL_MAX_ID + 5];
deque<pair<Index, Index> > dq;

void prepare() {
  signalDegrees[0] = true, dq.push_back(make_pair(0, 0));
  for (Index i = 0; i < InputPort.size(); i++)
    signalDegrees[InputPort[i]] = true,
    dq.push_back(make_pair(0, InputPort[i]));

  for (Index i = 0; i < allUnits.size(); i++) {
    verify(!signalDegrees[allUnits[i].first],
           ((string) "Multiple write access at signal " +
            to_str(allUnits[i].first))
               .c_str());
    signalDegrees[allUnits[i].first] = true;

    vector<Index> deps = allUnits[i].second.dependencies();
    degrees.push_back(deps.size());
    for (Index j = 0; j < deps.size(); j++) relatedUnit[deps[j]].push_back(i);
    if (allUnits[i].second.type == 8)
      dffs.push_back(i), dq.push_back(make_pair(0, allUnits[i].first));
  }

  for (Index i = 1; i <= MaxID; i++)
    if (!signalDegrees[i] && relatedUnit[i].size() != 0)
      dq.push_back(make_pair(0, i));

  Index currTcomb = 0;

  while (!dq.empty()) {
    pair<Index, Index> tp = dq.front();
    dq.pop_front();
    currTcomb = tp.first;
    for (Index i = 0; i < relatedUnit[tp.second].size(); i++) {
      Index x = relatedUnit[tp.second][i];
      if (--degrees[x] == 0) {
        topo.push_back(x);
        // no increasement
        if (allUnits[x].second.type == 0)
          dq.push_front(make_pair(tp.first, allUnits[x].first));
        else
          dq.push_back(make_pair(tp.first + 1, allUnits[x].first));
      }
    }
  }

  if (dffs.size() + topo.size() != allUnits.size())
    wrong("Combinational logic circuit includes cycle(s)");
  printf("Tcomb = %u, D_FF count = %llu\n", currTcomb, dffs.size());
  if (currTcomb > MaxTcomb) wrong("Tcomb exceeds MAX_TCOMB");
  if (dffs.size() > DFFMaximum) wrong("D_FF count exceeds DFF_MAXIMUM");
}

void handleDFFs() {
  for (Index i = 0; i < dffs.size(); i++) {
    Index x = dffs[i];
    allUnits[x].second.storage =
        SignalPool::read(allUnits[x].second.children[0].id);
  }
  for (Index i = 0; i < dffs.size(); i++) {
    Index x = dffs[i];
    SignalPool::write(allUnits[x].first, allUnits[x].second.storage);
  }
}

void setInput() {
  for (Index i = 0, x; i < InputPort.size(); i++) {
    verify(in >> x, "Input error");
    verify(x <= 1, "Unexpected input signal");
    SignalPool::write(InputPort[i], x);
  }
}

void run() {
  for (Index i = 0; i < topo.size(); i++) {
    Index x = topo[i];
    SignalPool::write(allUnits[x].first, allUnits[x].second.get());
  }
}

void execute(Index currCase) {
  printf("\rRunning case %u...", currCase);
  if (SimulateType == 0) {
    setInput();
    run();
    for (Index i = 0; i < OutputPort.size(); i++)
      out << SignalPool::readChar(OutputPort[i])
          << " \n"[i == OutputPort.size() - 1];
    if (dbg.is_open()) {
      dbg << "Case " << currCase << ":\n  ";
      for (Index i = 1; i <= MaxID; i++)
        dbg << SignalPool::readChar(i) << " \n"[i == MaxID];
      dbg << "\n";
    }
  } else {
    if (dbg.is_open()) {
      dbg << "Case " << currCase << ":\n";
    }
    for (Index t = 1; t <= ClockLoopTime; t++) {
      setInput();
      run();
      handleDFFs();
      run();
      for (Index i = 0; i < OutputPort.size(); i++)
        out << SignalPool::readChar(OutputPort[i])
            << " \n"[i == OutputPort.size() - 1];
      if (dbg.is_open()) {
        dbg << "  Loop " << t << ": ";
        for (Index i = 1; i <= MaxID; i++)
          dbg << SignalPool::readChar(i) << " \n"[i == MaxID];
      }
    }
    if (dbg.is_open()) {
      dbg << "\n";
    }
    out << "\n";
  }
}

}  // namespace Worker

int main(int argc, char **argv) {
  in.open(argc > 1 ? argv[1] : "data.in");
  verify(in.is_open(), "Can't open description file");
  verify(in >> CaseNum >> SimulateType >> MaxID >> ClockLoopTime >>
             DFFMaximum >> MaxTcomb >> MaxDegree >> InSignalNum >> OutSignalNum,
         "Input error");
  verify(SimulateType <= 1, "Undefined simulate type");
  verify(MaxID <= 1e5, "MAX_ID exceeds 1e5");
  verify(MaxID != 0, "MAX_ID should not be 0");
  for (Index i = 0, x; i < InSignalNum; i++) {
    verify(in >> x, "Input error");
    verify(x <= MaxID, "Input id exceeds MAX_ID");
    verify(x != 0, "ID 0 should be read-only");
    InputPort.push_back(x);
  }
  verify(is_unique(InputPort), "Input ids should be unique");
  for (Index i = 0, x; i < OutSignalNum; i++) {
    verify(in >> x, "Output error");
    verify(x <= MaxID, "Output id exceeds MAX_ID");
    OutputPort.push_back(x);
  }
  verify(is_unique(OutputPort), "Output ids should be unique");

  out.open(argc > 2 ? argv[2] : "data.out");
  verify(out.is_open(), "Can't open output file");
  if (argc > 3) {
    dbg.open(argv[3]);
    verify(dbg.is_open(), "Can't open debug file");
  }

  StringView::init();
  Worker::parseCmd();
  Worker::prepare();
  SignalPool::init();
  
  for (Index i = 1; i <= CaseNum; i++) Worker::execute(i);

  printf("\r%u case(s) runned.", CaseNum);

  return 0;
}