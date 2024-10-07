#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;

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

int n, q, dep[N], fa[N][20];
uint val[N], g[105][105];
vector<pair<int, uint > > es[N];

inline void dfs0(int u, int pre, uint w) {
    dep[u] = dep[pre] + 1; fa[u][0] = pre; val[u] = w;
    For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &[v, w] : es[u]) if (v ^ pre) dfs0(v, u, w);
}

inline int lca(int u, int v) {
    if (dep[v] > dep[u]) swap(u, v);
    rFor (i, 19, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 19, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

inline void init() {
    g[1][1] = g[2][1] = g[2][2] = 1; g[3][1] = g[3][3] = 2; g[3][2] = 3;
    For (i, 4, 65) For (j, 1, i) g[i][j] = 2 * (g[i - 1][j - 1] + g[i - 1][j] - g[i - 2][j - 1]);
}

int main() {
    init();
    io >> n >> q;
    int u, v, op; uint w;
    For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    dfs0(1, 0, 0);
    while (q--) {
        io >> op;
        if (op == 1) io >> u >> w, val[u] = w;
        else {
            io >> u >> v;
            int f = lca(u, v), x = dep[u] + dep[v] - 2 * dep[f];
            uint ans = 0;
            if (x <= 65) {
                for (int y = 1; u ^ f; u = fa[u][0], y++) ans += g[x][y] * val[u];
                for (int y = 1; v ^ f; v = fa[v][0], y++) ans += g[x][y] * val[v];
            }
            printf("%u\n", ans);
        }
    }

    return 0;
}
