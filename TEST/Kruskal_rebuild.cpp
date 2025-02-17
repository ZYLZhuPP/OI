#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define st first
#define nd second
#define mkp make_pair
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5, inf = 1e9;

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

int n, m, q, h[N], rt[N << 1];

namespace Seg {
    int tot;
    struct Node {
        int l, r, sz;
        Node() { l = r = sz = 0; }
    } o[N * 60];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline int copy(const int &p) { o[++tot] = o[p]; return tot; }
    inline void upd(int &p, int l, int r, const int &x) {
        if (l > x || r < x) return;
        p = copy(p); o[p].sz++;
        if (l == r) return;
        M; upd(goL, x); upd(goR, x);
    }
    inline int query(int p, int l, int r, int q, const int &k) {
        if (o[q].sz - o[p].sz < k) return -1;
        if (l == r) return l;
        int x = o[o[q].r].sz - o[rs].sz;
        M; return k<=x? query(goR, o[q].r, k): query(goL, o[q].l, k - x);
    }
}

namespace KR {
    vector<pair<int, pair<int, int > > > es;
    int pa[N << 1], tot, dfn[N << 1], dfn_[N << 1], tim, fa[N << 1][20], val[N << 1];
    vector<int > T[N << 1];
    inline int find(int u) { return pa[u]^u? pa[u] = find(pa[u]): u; }
    inline void dfs(int u, int pre) {
        dfn[u] = ++tim, rt[tim] = rt[tim - 1];
        if (u <= n) Seg::upd(rt[tim], 1, inf, h[u]);
        For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto &v : T[u]) dfs(v, u);
        dfn_[u] = tim;
    }
    inline void build() {
        val[0] = inf + 1;
        tot = n;
        For (i, 1, n) pa[i] = i;
        sort(es.begin(), es.end());
        for (auto &e : es) {
            int u = e.nd.st, v = e.nd.nd;
            int fu = find(u), fv = find(v);
            if (fu ^ fv) {
                int x = ++tot; pa[x] = pa[fu] = pa[fv] = x;
                T[x].pb(fu), T[x].pb(fv);
                fa[fu][0] = fa[fv][0] = x;
                val[x] = e.st;
            }
        }
        rFor (i, tot, 1) if (!dfn[i]) dfs(i, 0);
    }
    inline int jump(int u, int x) {
        rFor (i, 19, 0) if (val[fa[u][i]] <= x) u = fa[u][i];
        return u;
    }
}
using namespace KR;

int main() {
    io >> n >> m >> q;
    For (i, 1, n) io >> h[i];
    int u, v, w, k;
    while (m--) io >> u >> v >> w, es.pb(mkp(w, mkp(u, v)));
    build();
    while (q--) {
        io >> u >> w >> k;
        u = jump(u, w);
        printf("%d\n", Seg::query(rt[dfn[u] - 1], 1, inf, rt[dfn_[u]], k));
    }

    return 0;
}
