#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, m, q, dep[N], dfn[N], dfn_[N], tim, fa[N][18], to[N][18], ans[N], cnt[N];
vector<int > es[N], ad[N];
vector<array<int, 3 > > op[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

inline bool dmin(int &x, int y) { return dep[y]<dep[x]? x=y, 1: 0; }

inline void dfs0(int u, int pre) {
    dfn[u] = ++tim; dep[u] = dep[pre] + 1; fa[u][0] = to[u][0] = pre;
    For (i, 1, 17) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u);
    dfn_[u] = tim;
}

inline void dfs(int u, int pre) {
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u), dmin(to[u][0], to[v][0]);
}

inline int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 17, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 17, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

inline pair<int, int > find(int u, int f) {
    int res = 0;
    rFor (i, 17, 0) if (dep[to[u][i]] > dep[f]) u = to[u][i], res |= 1 << i;
    return {res, u};
}

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    For (i, 1, m) {
        io >> u >> v;
        int f = lca(u, v);
        dmin(to[u][0], f); dmin(to[v][0], f);
        if (dfn[u] > dfn[v]) swap(u, v);
        ad[dfn[u]].pb(dfn[v]);
    }
    dfs(1, 0);
    For (j, 1, 17) For (i, 1, n) to[i][j] = to[to[i][j - 1]][j - 1];
    io >> q;
    For (i, 1, q) {
        io >> u >> v;
        int f = lca(u, v);
        if (u == v) ans[i] = 0;
        else if (u == f || v == f) {
            v = f ^ u ^ v;
            auto [d, x] = find(v, f);
            ans[i] = d + 1;
        } else {
            auto [d1, x] = find(u, f); auto [d2, y] = find(v, f);
            ans[i] = d1 + d2 + 2;
            if (dfn[x] > dfn[y]) swap(x, y);
            op[dfn_[x]].pb({dfn_[y], i, 1});
            op[dfn_[x]].pb({dfn[y] - 1, i, -1});
            op[dfn[x] - 1].pb({dfn_[y], i, -1});
            op[dfn[x] - 1].pb({dfn[y] - 1, i, 1});
        }
    }
    For (i, 1, n) {
        for (auto &x : ad[i]) upd(x, 1);
        for (auto &[x, id, k] : op[i]) cnt[id] += k * query(x);
    }
    For (i, 1, q) printf("%d\n", ans[i] - (cnt[i] > 0));

    return 0;
}
