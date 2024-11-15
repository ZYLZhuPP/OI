#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;
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

int n, q, sz[N], son[N], co[N], s[N][2], dfn[N], pt[N], tim, fa[N], top[N];
vector<array<int, 2 > > es[N];

inline bool W(int u, int cu, int cv) { return son[u] && (cu ^ cv || s[u][!cu]); }
inline bool ok(int u, int cu, int cv) { return (s[u][0] + s[u][1]) && cu==cv && (!s[u][0] || !s[u][1]); }

namespace Seg {
    int o[N << 2][3], t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p][0] = o[ls][t[p]] + o[rs][t[p]], o[p][1] = o[ls][!t[p]] + o[rs][!t[p]], o[p][2] = o[ls][2] + o[rs][2]; }
    inline void rev(int p) { swap(o[p][0], o[p][1]); t[p] ^= 1; }
    inline void build(int p, int l, int r) {
        if (l == r) {
            int u = pt[l], x = W(u, co[u], co[son[u]]);
            if (ok(u, co[u], co[son[u]])) o[p][x] = 1; else o[p][2] = x;
            return;
        }
        M; build(goL); build(goR); up(p);
    }
    inline int query(int p, int l, int r, int x, int k) {
        k ^= t[p];
        if (l == r) return k ^ co[pt[x]];
        M; return x<=m? query(goL, x, k): query(goR, x, k);
    }
    inline void rev(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return rev(p);
        M; rev(goL, x, y); rev(goR, x, y); up(p);
    }
    inline void upd(int p, int l, int r, int x, int k) {
        if (l == r) {
            o[p][0] = o[p][1] = o[p][2] = 0;
            int u = pt[x], cu = !query(1, 2, n, x, 0), cv = query(1, 2, n, dfn[son[u]], 0), x = W(u, cu, cv);
            if (ok(u, cu, cv)) o[p][!(x ^ k)] = 1; else o[p][2] = x;
            return;
        }
        k ^= t[p]; M; x<=m? upd(goL, x, k): upd(goR, x, k); up(p);
    }
}
using namespace Seg;

inline void dfs0(int u, int pre) {
    fa[u] = pre; sz[u] = 1;
    for (auto &[v, w] : es[u]) if (v ^ pre) {
        co[v] = w; dfs0(v, u); sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

inline void dfs1(int u, int t) {
    pt[dfn[u] = ++tim] = u; top[u] = t;
    if (son[u]) dfs1(son[u], t);
    for (auto &[v, w] : es[u]) if (!top[v]) dfs1(v, v), s[u][co[v]]++;
}

inline void Upd(int u) {
    int lst = -1;
    while (u) {
        if (~lst) s[u][lst]++, s[u][!lst]--;
        if (u == 1) break;
        upd(1, 2, n, dfn[u], 0);
        int f = top[u];
        rev(1, 2, n, dfn[f], dfn[u]);
        lst = query(1, 2, n, dfn[f], 0);
        u = fa[f];
    }
}

int main() {
    io >> n;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    dfs0(1, 0); dfs1(1, 1);
    build(1, 2, n);
    io >> q;
    while (q--) {
        io >> u >> v;
        Upd(u); Upd(v);
        int x = query(1, 2, n, 2, 0);
        s[1][x]++;
        printf("%d\n", o[1][1] + o[1][2] + bool(s[1][0]) + bool(s[1][1]));
        s[1][x]--;
    }

    return 0;
}
