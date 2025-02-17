#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e4 + 5, inf = 1e9;

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

int n, Q, w[N];

struct V {
    int mx, s;
    V() { mx = -inf; s = 0; }
    V(int v): mx(v), s(v) { }
    V operator + (const V &a) const {
        V r = a;
        r.mx = max(r.mx, mx); r.s += s;
        return r;
    }
};

namespace Seg {
    typedef V Node;
    Node o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] + o[rs]; }
    inline void upd(int p, int l, int r, const int &x, const int &v) {
        if (l > x || r < x) return;
        if (l == r) return void(o[p] = Node(v));
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline Node query(int p, int l, int r, const int &x, const int &y) {
        if (l > y || r < x) return Node();
        if (x <= l && r <= y) return o[p];
        M; return query(goL, x, y) + query(goR, x, y);
    }
}

namespace Heavy {
    int fa[N], top[N], son[N], siz[N], dep[N], dfn[N], dfn_[N], tim;
    vector<int > es[N];
    inline void dfs0(int u, int pre) {
        fa[u] = pre; dep[u] = dep[pre] + 1; siz[u] = 1;
        for (auto &v : es[u]) if (v ^ pre) {
            dfs0(v, u); siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
    inline void dfs1(int u, int t) {
        dfn[u] = ++tim; top[u] = t;
        if (son[u]) dfs1(son[u], t);
        for (auto &v : es[u]) if (!top[v]) dfs1(v, v);
        dfn_[u] = tim;
    }
    void init(int rt = 1) {
        dfs0(rt, 0); dfs1(rt, rt);
        For (i, 1, n) Seg::upd(1, 1, n, dfn[i], w[i]);
    }
    void upd(int u, const int &v) {
        Seg::upd(1, 1, n, dfn[u], v);
    }
    V query(int u, int v) {
        V res;
        while (top[u] ^ top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            res = res + Seg::query(1, 1, n, dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) swap(u, v);
        res = res + Seg::query(1, 1, n, dfn[v], dfn[u]);
        return res;
    }
}
using namespace Heavy;

int main() {
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (i, 1, n) io >> w[i];
    init();
    io >> Q;
    while (Q--) {
        char op[8];
        int x, y;
        scanf("%s", op); io >> x >> y;
        if (op[1] == 'H') {
            upd(x, y);
        } else if (op[1] == 'M') {
            printf("%d\n", query(x, y).mx);
        } else if (op[1] == 'S') {
            printf("%d\n", query(x, y).s);
        }
    }

    return 0;
}
