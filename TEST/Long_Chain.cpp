#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 1e5 + 5;
const lf inf = 1e18;
inline void cmax(lf &x, const lf &y) { x = y>x? y: x; }

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

int n, L, U, ww[N];
lf m, ans, f[N], g[N];

namespace Seg {
    lf o[N << 2];
    inline void init() { fill(o, o + (N << 2), -inf); }
#define P int p, int l, int r
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(P, const int &x, const lf &v) {
        if (l > x || r < x) return;
        cmax(o[p], v);
        if (l == r) return;
        M; upd(goL, x, v); upd(goR, x, v);
    }
    inline lf query(P, const int &x, const int &y) {
        if (l > y || r < x) return -inf;
        if (x <= l && r <= y) return o[p];
        M; return max(query(goL, x, y), query(goR, x, y));
    }
}

namespace Long {
    struct Edge { int to, w; };
    vector<Edge > es[N];
    int fa[N], top[N], son[N], dep[N], dfn[N], dfn_[N], tim;
    inline void dfs0(int u, int pre) {
        fa[u] = pre;
        for (auto &e : es[u]) if (e.to ^ pre) {
            int v = e.to;
            dfs0(v, u);
            if (dep[v] + 1 > dep[u]) dep[u] = dep[son[u] = v] + 1, ww[u] = e.w;
        }
    }
    inline void dfs1(int u, int t) {
        dfn[u] = ++tim; top[u] = t;
        if (son[u]) dfs1(son[u], t);
        for (auto &e : es[u]) if (!top[e.to]) dfs1(e.to, e.to);
        dfn_[u] = tim;
    }
    inline void init(int rt = 1) {
        dfs0(rt, 0); dfs1(rt, rt);
    }
}
using namespace Long;

inline void solve(int u, int pre) {
    int pu = dfn[u];
    g[u] = f[pu] = 0;
    if (son[u]) solve(son[u], u), g[u] = g[son[u]] + ww[u] - m, f[pu] = -g[u];
    cmax(ans, g[u] + Seg::query(1, 1, n, pu + L, pu + min(dep[u], U)));
    Seg::upd(1, 1, n, pu, f[pu]);
    for (auto &e : es[u]) if (e.to ^ son[u] && e.to ^ pre) {
        int v = e.to; lf w = e.w - m;
        solve(v, u);
        For (i, dfn[v], dfn[v] + dep[v]) {
            int x = i - dfn[v] + 1;
            cmax(ans, w + (g[v] + f[i]) + (g[u] + Seg::query(1, 1, n, pu + max(0, L - x), pu + min(dep[u], U - x))));
        }
        For (i, dfn[v], dfn[v] + dep[v]) {
            int x = i - dfn[v] + 1;
            cmax(f[pu + x], w + (g[v] + f[i]) - g[u]);
            Seg::upd(1, 1, n, pu + x, f[pu + x]);
        }
    }
}

int main() {
    io >> n >> L >> U;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    init();
    lf l = 0, r = 1e6;
    while (r - l > 1e-5) {
        m = (l + r) / 2;
        Seg::init();
        ans = -inf;
        solve(1, 0);
        if (ans >= 0) l = m;
        else r = m;
    }
    printf("%.3lf", l);

    return 0;
}
