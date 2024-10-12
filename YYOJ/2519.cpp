#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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
ll d[N], f[N], g[N], h[N], up[N], s[N][20], ans;
vector<array<int, 2 > > es[N];

inline void dfs0(int u, int pre) {
    dep[u] = dep[pre] + 1; fa[u][0] = pre;
    For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &[v, w] : es[u]) if (v ^ pre) {
        d[v] = d[u] + w; dfs0(v, u); g[v] = max(f[v] + w, 0ll); f[u] += g[v];
    }
}

inline void dfs1(int u, int pre) {
    For (i, 1, 19) s[u][i] = s[u][i - 1] + s[fa[u][i - 1]][i - 1];
    for (auto &[v, w] : es[u]) if (v ^ pre) {
        h[v] = s[v][0] = f[u] - g[v];
        up[v] = max(w + up[u] + h[v], 0ll);
        dfs1(v, u);
    }
}

inline int lca(int u, int v) {
    if (dep[v] > dep[u]) swap(u, v);
    rFor (i, 19, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 19, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

inline ll query(int &u, int v) {
    ll r = 0;
    rFor (i, 19, 0) if (dep[fa[u][i]] > dep[v]) r += s[u][i], u = fa[u][i];
    return r;
}

int main() {
    io >> n;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    dfs0(1, 0);
    dfs1(1, 0);
    io >> q;
    while (q--) {
        io >> u >> v;
        int fa = lca(u, v);
        ans = d[u] + d[v] - 2 * d[fa];
        if (u == v) ans += up[v] + f[v];
        else if (fa == u || fa == v) {
            v = fa ^ u ^ v; u = fa;
            ans += f[v];
            ans += query(v, u);
            ans += h[v] + up[u];
        } else {
            ans += f[v] + f[u];
            ans += query(v, fa) + query(u, fa);
            ans += f[fa] - g[u] - g[v] + up[fa];
        }
        printf("%lld\n", ans);
    }

    return 0;
}
