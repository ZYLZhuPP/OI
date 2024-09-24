#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r = 1; for (; b; mul(a, a), b >>= 1) if (b & 1) mul(r, a); return r; }

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

int n, sz[N], fac[N], g[N], gg[N], f[N][N], h[N][N], p[N][N];
vector<int > es[N];

inline void dfs0(int u, int pre) {
    sz[u] = 1; g[u] = 1; int d = 0;
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u), sz[u] += sz[v], d++, mul(g[u], g[v]);
    mul(g[u], fac[d]);
    gg[u] = qPow(g[u], Mo - 2);
}

inline void init() {
    fac[0] = 1;
    For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i);
}

inline void dfs(int u, int pre) {
    For (i, 1, n) h[i + 1][0] = f[u][i];
    int d = 0, x = 1;
    for (auto &v : es[u]) if (v ^ pre) {
        rFor (i, n, 1) For (j, 0, d) if (h[i][j]) add(h[i + sz[v]][j + 1], h[i][j]);
        d++; mul(x, g[v]);
    }
    for (auto &v : es[u]) if (v ^ pre) {
        memcpy(p, h, sizeof h);
        int y = ml(x, gg[v]);
        For (i, 1, n) For (j, 0, d) if (p[i][j]) add(p[i + sz[v]][j + 1], -p[i][j]), add(f[v][i], ml(ml(p[i][j], y), ml(fac[j], fac[d - j - 1])));
    }
    For (i, 1, n) For (j, 0, d) h[i][j] = 0;
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u);
}

int main() {
    init();
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    f[1][1] = 1;
    dfs(1, 0);
    For (i, 1, n) For (j, 1, n) printf("%d%c", ml(f[i][j], g[i]), " \n"[j==n]);

    return 0;
}
