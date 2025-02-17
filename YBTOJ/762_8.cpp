#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, inf = 1e9;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, ans;

namespace Trie {
    const int S = 2.5e7;
    int ch[S][2], sz[S], tot, rub[S], top;
    inline int node() { return top? rub[top--]: ++tot; }
    inline void del(int &p) { rub[++top] = p; sz[p] = 0; p = 0; }
    inline void Del(int &p) { if (!p) return; Del(ch[p][0]); Del(ch[p][1]); del(p); }
    inline void upd(int &p, int k, int v, const int &d) {
        if (!p) p = node();
        sz[p] += d; //if (sz[p] < 0) cout << v << endl; assert(sz[p] >= 0);
        if (~k) upd(ch[p][v >> k & 1], k - 1, v, d); //else if (v == 4) cout << v << d << endl;
        if (!sz[p]) del(p);
    }
    inline int query(int p, int v) {
        int r = 0;
        rFor (i, 20, 0) {
            int c = v >> i & 1;
            if (ch[p][!c]) r |= 1 << i, p = ch[p][!c];
            else p = ch[p][c];
        }
        //cout << endl;
        return r;
    }
}

namespace SGT {
    const double alp = 0.75;
    typedef pair<int, int > P;
#define st first
#define nd second
    int rt, tot, id[N], len, v_;
    struct Node {
        int l, r, sz, msz, v, t, rt;
        P mx;
        Node() { l = r = sz = msz = v = t = rt = 0; mx = P(-inf, -inf); }
        Node(int v): v(v) { l = r = t = rt = 0; sz = msz = 1; Trie::upd(t, 20, v, 1); mx = P(v, -inf); }
    } o[N];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
    inline P Pmax(const P &a, const P &b) {
        int x = max(a.st, b.st), y = min(a.st, b.st);
        return P(x, max(y, max(a.nd, b.nd)));
    }
    inline void up(int p) {
        if (!p) return;
        o[p].sz = o[ls].sz + o[rs].sz + 1;
        o[p].msz = max(o[p].msz, o[p].sz);
        o[p].mx = Pmax(P(o[p].v, -inf), Pmax(o[ls].mx, o[rs].mx));
    }
    inline void build(int &p, const int &l, const int &r) {
        if (l > r) return void(p = 0);
        M; p = id[m];
        For (i, l, r) Trie::upd(o[p].rt, 20, o[id[i]].v, 1);
        build(ls, l, m - 1); build(rs, m + 1, r); up(p);
    }
    inline void pia(int p) { if (!p) return; pia(ls); id[++len] = p; o[p].sz = o[p].msz = 0; Trie::Del(o[p].rt); pia(rs); }
    inline int kth(int p, const int &k) {
        if (k == o[ls].sz + 1) return o[p].v;
        return k<=o[ls].sz? kth(ls, k): kth(rs, k - o[ls].sz - 1);
    }
    inline void upd(int p, const int &k, const int &v, const int &v_) {
    //cout << p << ":\n";
        Trie::upd(o[p].rt, 20, v_, -1);
        Trie::upd(o[p].rt, 20, v, 1);
        if (k == o[ls].sz + 1) {
            Trie::Del(o[p].t);
            Trie::upd(o[p].t, 20, o[p].v = v, 1);
            return up(p);
        }
        k<=o[ls].sz? upd(ls, k, v, v_): upd(rs, k - o[ls].sz - 1, v, v_); up(p);
    }
    inline void ins(int &p, const int &k, const int &v) {
    //cout << p << ":\n";
        if (!p) { o[p = ++tot] = Node(v); Trie::upd(o[p].rt, 20, v, 1); return; }
        Trie::upd(o[p].rt, 20, v, 1);
        k<=o[ls].sz+1? ins(ls, k, v): ins(rs, k - o[ls].sz - 1, v); up(p);
        if (max(o[ls].msz, o[rs].msz) > alp * o[p].msz) len = 0, pia(p), build(p, 1, len);
    }
    inline void del(int &p, const int &k, const int &v) {
        Trie::upd(o[p].rt, 20, v, -1);
        if (k == o[ls].sz + 1) {
            Trie::Del(o[p].t);
            if (!ls || !rs) p = ls | rs;
            //else if (!o[rs].l) o[rs].l = ls, p = rs, cout << "?";
            else {
                int x, *f = &rs, v_;
                len = 0; for (x = rs; o[x].l; x = o[x].l) f = &o[x].l, id[++len] = x;
                //cout << len << "!\n";
                v_ = o[x].v; *f = o[x].r;
                rFor (i, len, 1) Trie::upd(o[id[i]].rt, 20, v_, -1), up(id[i]);
                o[x].l = ls; o[x].r = rs; o[x].rt = o[p].rt; p = x;
            }
            return up(p);
        }
        k<=o[ls].sz+1? del(ls, k, v): del(rs, k - o[ls].sz - 1, v); up(p);
    }
    inline P split(int p, const int &l, const int &r) {
        //cout << o[p].v << o[p].sz << l << r << endl;
        if (!p || l > o[p].sz || r < 1) return P(-inf, -inf);
        if (l <= 1 && o[p].sz <= r) return id[++len] = o[p].rt, o[p].mx;
        int x = o[ls].sz + 1; P res = P(-inf, -inf);
        if (l <= x && x <= r) id[++len] = o[p].t, res.st = o[p].v; //cout << o[p].v << ':';
        return Pmax(res, Pmax(split(ls, l, r), split(rs, l - x, r - x)));
    }
}
using namespace SGT;

inline int solve(const int &l, const int &r) {
    len = 0; int x = split(rt, l, r).nd, res = 0; //cout << "x = " << x << endl;
    //cout << len << endl;
    For (i, 1, len) res = max(res, Trie::query(id[i], x));
    return res;
}

int main() {
    char op;
    int x, y;
    io >> n >> m;
    For (i, 1, n) io >> x, o[id[i] = i] = Node(x);
    build(rt, 1, tot = n); //cout << Trie::tot << endl;
    while (m--) {
        cin >> op; //cout << op;
//        cout << "rt = " << rt << endl;
//        For (i, 1, o[rt].sz) cout << kth(rt, i) << " ";
//        cout << endl;
        if (op == 'I') {
            io >> x >> y; x = (x + ans) % o[rt].sz + 1; y = (y + ans) % 1048576;
            //cout << x << " " << y << endl;
            ins(rt, x, y);
        } else if (op == 'D') {
            io >> x; x = (x + ans) % o[rt].sz + 1;
            //cout << x << kth(rt, x) << endl;
            del(rt, x, kth(rt, x));
        } else if (op == 'C') {
            io >> x >> y; x = (x + ans) % o[rt].sz + 1; y = (y + ans) % 1048576;
            //cout << x << y << endl;
            upd(rt, x, y, kth(rt, x));
        } else if (op == 'F') {
            io >> x >> y; x = (x + ans) % o[rt].sz + 1; y = (y + ans) % o[rt].sz + 1;
            //cout << x << y << endl;
            printf("%d\n", ans = solve(x, y));
        }
    }

    return 0;
}
