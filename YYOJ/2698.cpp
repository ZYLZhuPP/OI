#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef array<int, 2 > P;
typedef long long ll;
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

int ID, n, K, m, fa[N], sz[N], son[N], top[N], dfn[N], dfn_[N], tim, pt[N], L[N << 1], U[N << 1], X[N << 1];
ll ans[N], res;
vector<int > es[N], ops[N << 2];
multiset<int > se[N];

inline void dfs0(int u) {
    sz[u] = 1;
    for (auto &v : es[u]) {
        dfs0(v);
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

inline void dfs1(int u, int t) {
    pt[dfn[u] = ++tim] = u; top[u] = t;
    if (son[u]) dfs1(son[u], t);
    for (auto &v : es[u]) if (v ^ son[u]) dfs1(v, v);
    dfn_[u] = tim;
}

namespace Seg {
    struct Node { int mn, t; P Mn; } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void build(int p, int l, int r) {
        o[p].Mn = {0, l};
        if (l == r) return;
        M; build(goL); build(goR);
    }
    inline void up(int p) { o[p].mn = min(o[ls].mn, o[rs].mn) + o[p].t; }
    inline void mark(int p, const int &d) { o[p].mn += d; o[p].t += d; }
    inline void upd(int p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, d);
        M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline int query(int p, int l, int r, int x, int y, int k) {
        if (l > y || r < x || o[p].mn + k > 0) return 0;
        if (l == r) return l;
        k += o[p].t; M, u = query(goR, x, y, k); return u? u: query(goL, x, y, k);
    }
    inline void Up(int p) { o[p].Mn = min(o[ls].Mn, o[rs].Mn); }
    inline void upd(int p, int l, int r, int x, const int &v) {
        if (l == r) return o[p].Mn = {v, x}, void();
        M; x<=m? upd(goL, x, v): upd(goR, x, v); Up(p);
    }
    inline P query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return {inf, 0};
        if (x <= l && r <= y) return o[p].Mn;
        M; return min(query(goL, x, y), query(goR, x, y));
    }
}
using namespace Seg;

inline int Query(int u) {
    int f = top[u], v = query(1, 1, n, dfn[f], dfn[u], 0);
    return v? pt[v]: Query(fa[f]);
}

inline void Upd(int u, const int &d) { for (int f; f = top[u], u; u = fa[f]) upd(1, 1, n, dfn[f], dfn[u], d); }

inline void add(int u, const int &x) {
    se[u].insert(x);
    upd(1, 1, n, dfn[u], *se[u].begin());
    Upd(u, -1);
}

inline void del(int u, const int &x) {
    se[u].erase(se[u].find(x));
    upd(1, 1, n, dfn[u], *se[u].begin());
    Upd(u, 1);
}

inline void ins(int p, int l, int r, int x, int y, const int &v) {
    if (l > y || r < x) return;
    if (x <= l && r <= y) return ops[p].pb(v);
    M; ins(goL, x, y, v); ins(goR, x, y, v);
}

inline void solve(int p, int l, int r) {
    vector<array<int, 4 > > back;
    for (auto &i : ops[p]) {
        int u = U[i], x = X[i], f = Query(u);
        auto [y, v] = query(1, 1, n, dfn[f], dfn_[f]); v = pt[v];
        //cerr << u << " " << x << " " << v << " " << y << endl;
        if (x > y) {
            back.pb({u, x, v, y});
            res += x - y;
            del(v, y); add(u, x);
        }
    }
    if (l == r) ans[l] = res;
    else { M; solve(goL), solve(goR); }
    while (!back.empty()) {
        auto [u, x, v, y] = back.back(); back.pop_back();
        res -= x - y;
        del(u, x); add(v, y);
    }
}

int main() {
    io >> ID;
    io >> n >> K >> m; m++;
    build(1, 1, n);
    For (i, 1, n) se[i].insert(0), se[i].insert(inf);
    For (i, 2, n) io >> fa[i], es[fa[i]].pb(i);
    dfs0(1); dfs1(1, 1);
    For (i, 1, K) io >> U[i] >> X[i], L[i] = 1;
    int x, op;
    For (i, 2, m) {
        io >> op;
        if (op == 1) K++, io >> U[K] >> X[K], L[K] = i;
        else io >> x, ins(1, 1, m, L[x], i - 1, x), L[x] = 0;
    }
    For (i, 1, K) if (L[i]) ins(1, 1, m, L[i], m, i);
    solve(1, 1, m);
    For (i, 1, m) printf("%lld ", ans[i]);

    return 0;
}
