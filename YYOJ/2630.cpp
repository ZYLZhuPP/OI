#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, m, S, T, s[N];
vector<array<int, 2 > > op[N];
vector<array<int, 3 > > OP;
deque<array<int, 2 > > q[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int d) { for (; x < N; x += lowbit(x)) add(o[x], d); }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) add(r, o[x]); return r; }
}
using namespace BIT;

int main() {
    io >> n >> m >> S; T = qPow(S, Mo - 2);
    int l, r, v;
    For (i, 1, m) {
        io >> l >> r >> v;
        op[v].pb({l, r});
    }
    For (i, 1, S) if (!op[i].empty()) {
        sort(op[i].begin(), op[i].end());
        vector<array<int, 2 > > a;
        for (auto &[l, r] : op[i]) {
            while (!a.empty() && a.back()[1] >= r) a.pop_back();
            if (a.empty() || l > a.back()[0]) a.pb({l, r});
        }
        op[i] = a;
        for (auto &[l, r] : a) OP.pb({l, r, i});
    }
    sort(OP.begin(), OP.end());
    for (auto &[l, r, v] : OP) {
        int x = ml(Mo + 1 - query(l - 1), qPow(T, r - l + 1));
        while (!q[v].empty() && q[v].front()[0] < l) add(s[v], -ml(q[v].front()[1], qPow(S, q[v].front()[0]))), q[v].pop_front();
        add(x, -ml(s[v], qPow(T, r)));
        upd(r, x);
        q[v].pb({r, x}); add(s[v], ml(x, qPow(S, r)));
    }
    printf("%d", ml(Mo + 1 - query(n), qPow(S, n)));

    return 0;
}
