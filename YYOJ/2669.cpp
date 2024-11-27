#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e4 + 5;

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

int n, q, fa[N][16], dep[N], dfn[N], dfn_[N], tim, be[N], tot, B, a[N], b[N], c[N], C, ans[N], vis[N], X, Y, F;
vector<int > pt[N], es[N];

struct Q {
    int u, v, id; ll w;
    bool operator < (const Q &a) const { return be[u]^be[a.u]? be[u]<be[a.u]: dfn[v]<dfn[a.v]; }
};
vector<Q > qs;

namespace Seg {
    ll o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(int p, int l, int r, int x, int d) {
        o[p] += d;
        if (l == r) return;
        M; x<=m? upd(goL, x, d): upd(goR, x, d);
    }
    inline int query(int p, int l, int r, ll x) {
        if (o[p] < x) return -1;
        if (l == r) return c[l];
        M; return x<=o[ls]? query(goL, x): query(goR, x - o[ls]);
    }
}
using namespace Seg;

inline int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 15, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 15, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

inline void dfs0(int u, int pre) {
    dfn[u] = ++tim; fa[u][0] = pre; dep[u] = dep[pre] + 1;
    For (i, 1, 15) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &v : es[u]) if (v ^ pre) {
        dfs0(v, u); for (auto &x : pt[v]) pt[u].pb(x); pt[v].resize(0);
        if (pt[u].size() >= B) {
            ++tot;
            for (auto &x : pt[u]) be[x] = tot;
            pt[u].resize(0);
        }
    }
    pt[u].pb(u);
    dfn_[u] = tim;
}

inline bool in(int x, int y) { return dfn[y] <= dfn[x] && dfn[x] <= dfn_[y]; }
inline bool on(int x) { return in(x, F) && (in(X, x) || in(Y, x)); }
inline void go(int u, int f) {
    while (dep[u] >= dep[f]) {
        bool x = on(u);
        if (x && !vis[u]) upd(1, 1, C, a[u], b[u]), vis[u] = 1;
        else if (!x && vis[u]) upd(1, 1, C, a[u], -b[u]), vis[u] = 0;
        u = fa[u][0];
    }
}
inline void Go(int u, int v) {
    int f = lca(u, v);
    go(u, f); go(v, f);
}

int main() {
    io >> n >> q; B = sqrt(n);
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    ++tot; for (auto &x : pt[1]) be[x] = tot;
    For (i, 1, n) io >> a[i] >> b[i], c[i] = a[i];
    sort(c + 1, c + n + 1); C = unique(c + 1, c + n + 1) - c - 1;
    For (i, 1, n) a[i] = lower_bound(c + 1, c + C + 1, a[i]) - c;

    ll w;
    For (i, 1, q) io >> u >> v >> w, qs.pb({u, v, i, w});
    sort(qs.begin(), qs.end());
    u = 1, v = 1;
    for (auto &[x, y, id, w] : qs) {
        X = x, Y = y, F = lca(X, Y);
        Go(u, x); Go(v, y);
        u = x; v = y;
        ans[id] = query(1, 1, C, w);
    }
    For (i, 1, q) ~ans[i]? printf("%d\n", ans[i]): puts("Impossible ");

    return 0;
}
