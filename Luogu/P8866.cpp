#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 605, M = 2e6 + 5;

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

int T, n, m, K, a[M], pos[N], emp;
vector<array<int, 3 > > ans;
vector<int > q;
deque<int > b[N];

inline void op1(int p) { ans.pb({1, p, 0}); }
inline void op2(int p1, int p2) { ans.pb({2, p1, p2}); }

inline void remove(int x) {
    int p = pos[x]; q.pb(p);
    if (x == b[p].back()) op1(p), b[p].pop_back();
    else op1(emp), op2(emp, p), b[p].pop_front();
    pos[x] = 0;
}

inline void put(int x) {
    int p = q.back(); q.pop_back();
    op1(p); b[p].pb(x); pos[x] = p;
}

inline bool solve(int x) {
    if (pos[x]) return remove(x), 1;
    if (!q.empty()) return put(x), 1;
    return 0;
}

int main() {
    io >> T;
    while (T--) {
        ans.resize(0);
        io >> n >> m >> K; emp = n;
        For (i, 1, m) io >> a[i];
        q.resize(0); For (i, 1, n - 1) q.pb(i), q.pb(i);
        For (i, 1, m) {
            int x = a[i];
            if (!solve(x)) {
                int r = i + 1; while (a[r] ^ x && a[r] == b[pos[a[r]]].back()) r++;
                if (a[r] == x) {
                    op1(emp);
                    For (j, i + 1, r - 1) solve(a[j]);
                    op1(emp);
                } else {
                    int y = b[pos[a[r]]].back(), cnt = 0, p = pos[y];
                    For (j, i + 1, r - 1) cnt += a[j] == y;
                    if (cnt & 1) {
                        op1(emp); b[emp].pb(x); pos[x] = emp; q.pb(emp);
                        For (j, i + 1, r - 1) if (a[j] == y) op1(p); else solve(a[j]);
                        op1(p); b[p].clear(); pos[a[r]] = pos[y] = 0; emp = p;
                    } else {
                        op1(p); b[p].pb(x); pos[x] = p;
                        For (j, i + 1, r - 1) if (a[j] == y) op1(emp); else solve(a[j]);
                        op1(emp); op2(emp, p); b[p].pop_front(); pos[a[r]] = 0;
                    }
                }
                i = r;
            }
        }
        printf("%d\n", (int)ans.size());
        for (auto &[op, l, r] : ans) op==1? printf("1 %d\n", l): printf("2 %d %d\n", l, r);
    }

    return 0;
}
