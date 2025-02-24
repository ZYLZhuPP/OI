#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e5 + 5;
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

namespace Seg {
    struct Node { int l, r, c, mx; } o[N << 5];
    int tot, rt[N];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].c = o[ls].c + o[rs].c; o[p].mx = max(o[ls].mx + o[rs].c, o[rs].mx); }
    inline void upd(int &p, int l, int r, int x, const int &d) {
        if (!p) p = ++tot;
        if (l == r) return o[p].c += d, o[p].mx = o[p].c? x + o[p].c: 0, void();
        M; x<=m? upd(goL, x, d): upd(goR, x, d); up(p);
    }
    inline void merge(int &p, int l, int r, int q) {
        if (!p || !q) return p |= q, void();
        if (l == r) return o[p].c += o[q].c, o[p].mx = o[p].c? l + o[p].c: 0, void();
        M; merge(goL, o[q].l); merge(goR, o[q].r); up(p);
    }
}
using namespace Seg;

int n, m, pa[N], fa[N], dep[N], dfn[N], dfn_[N], tim, cnt[N], be[N], ans;
vector<int > T[N], del[N];

inline int find(int x) { return pa[x]^x? pa[x] = find(pa[x]): x; }

inline void dfs0(int u) {
    dfn[u] = ++tim;
    for (auto &v : T[u]) dep[v] = dep[u] + 1, be[v] = u? be[u]: v, dfs0(v);
    dfn_[u] = tim;
}

inline void add(int u, int v) { cnt[v]++; del[u].pb(dep[v]); }

inline void dfs1(int u) {
    for (auto &v : T[u]) dfs1(v), merge(rt[u], 1, 2 * n, rt[v]);
    upd(rt[u], 1, 2 * n, dep[u], cnt[u]);
    for (auto &x : del[u]) upd(rt[u], 1, 2 * n, x, -1);
    cmax(ans, o[rt[u]].mx - dep[u]);
}

int main() {
    io >> n;
    For (i, 1, n) pa[i] = i;
    For (i, 1, n) io >> fa[i], fa[i + n] = fa[i] + n, pa[find(i)] = find(fa[i]);
    For (i, 1, n) if (pa[i] == i) {
        int u = i;
        while (pa[u]) pa[u] = 0, u = fa[u];
        fa[u + n] = fa[u]; fa[u] = 0;
    }
    For (i, 1, 2 * n) T[fa[i]].pb(i);
    dfs0(0);
    io >> m;
    int u, v;
    For (i, 1, m) {
        io >> u >> v;
        if (dfn[v] <= dfn[u] && dfn[u] <= dfn_[v]) add(v, u);
        else if (dfn[v] <= dfn[u + n] && dfn[u + n] <= dfn_[v]) add(v, u + n), add(be[v], u);
        else return puts("-1"), 0;
    }
    dfs1(0);
    printf("%d", ans);

    return 0;
}
