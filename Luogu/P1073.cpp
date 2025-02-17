#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, m, w[N], mn[N], f[N];
vector<int > G[N];

inline void dfs(int u, int x, int pre) {
    cmin(x, w[u]);
    if (cmin(mn[u], x) | cmax(f[u], max(f[pre], w[u] - x)))
        for (auto &v : G[u]) dfs(v, x, u);
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> w[i], mn[i] = 101;
    int u, v, k;
    For (i, 1, m) {
        io >> u >> v >> k;
        G[u].pb(v);
        if (k == 2) G[v].pb(u);
    }
    dfs(1, 101, 0);
    printf("%d", f[n]);

    return 0;
}
