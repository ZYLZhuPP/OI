#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef pair<ll, int > P;
const int N = 2e5 + 5;
const ll INF = 1e18;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, q, e[N], dfn[N], dfn_[N], tim, pt[N], sz[N], son[N], top[N], val[N], dep[N], fa[N];
int a[N], b[N], c[N];
ll mx[N], s[N], w[N], ans, dd[N];
vector<int > es[N];

inline bool on(int u) { return u==e[u] || son[u]==e[u]; }

namespace BIT {
    ll o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline ll query(int x) { ll r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}

namespace Seg {
    struct Node {
        ll val, tag; P mn;
    } o[N << 2];
#define ls p << 1 
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].mn = min(o[ls].mn, o[rs].mn); o[p].val = o[ls].val + o[rs].val; }
    inline void mark(int p, ll d) { if (o[p].val) o[p].mn.st -= 2 * d; o[p].tag += d; }
    inline void down(int p) { if (o[p].tag) mark(ls, o[p].tag), mark(rs, o[p].tag), o[p].tag = 0; }
    inline void build(int p, int l, int r) {
        if (l == r) {
            int x = pt[l]; o[p].mn.nd = l; o[p].tag = 0;
            if (e[x] && !on(x)) o[p].mn.st = dd[x], o[p].val = val[x];
            else o[p].mn.st = INF, o[p].val = 0;
            return;
        }
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x) {
        if (l > x || r < x) return;
        if (l == r) {
            int x = pt[l]; o[p].mn.nd = l;
            if (e[x] && !on(x)) o[p].mn.st = dd[x], o[p].val = val[x];
            else o[p].mn.st = INF, o[p].val = 0;
            return;
        }
        down(p); M; upd(goL, x); upd(goR, x); up(p);
    }
    inline void upd(int p, int l, int r, int x, int y, int d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, d), ans -= 2 * d * o[p].val, void();
        down(p); M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline P query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return {INF, 0};
        if (x <= l && r <= y) return o[p].mn;
        down(p); M; return min(query(goL, x, y), query(goR, x, y));
    }
    inline void find(int p, int l, int r, int x) {
        if (l > x || r < x) return;
        if (l == r) {
            int x = pt[l];
            s[x] += 2 * o[p].tag;
            if (e[x] && !on(x)) dd[x] -= 2 * o[p].tag;
            o[p].tag = 0;
            return;
        }
        down(p); M; find(goL, x); find(goR, x);
    }
}
using namespace Seg;

inline void dfs0(int u, int pre) {
    sz[u] = 1; dep[u] = dep[pre] + 1; fa[u] = pre;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs0(v, u); sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

inline void dfs1(int u, int t) {
    dfn[u] = ++tim; pt[tim] = u; top[u] = t;
    if (son[u]) dfs1(son[u], t);
    for (auto &v : es[u]) if (!top[v]) dfs1(v, v);
    dfn_[u] = tim;
}

inline int lca(int u, int v) {
    while (top[u] ^ top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u]<dep[v]? u: v;
}

inline ll get(int u) { return (e[u]? dd[u]: (s[u] & 1)) * val[u]; }

inline ll W(int i) { return w[i] + BIT::query(dfn_[i]) - BIT::query(dfn[i] - 1); }

inline void change(int u, int i, int j, int d) {
    if (!i && !j) return;
    find(1, 1, n, dfn[u]); ans -= get(u); s[u] += ((i>0) + (j>0)) * d;
    if (!i || !j) { i |= j; if (2 * W(i) > s[u]) e[u] = i; }
    if (e[u]) { dd[u] = 2 * W(e[u]) - s[u]; e[u] *= dd[u] > 0; }
    ans += get(u);
    upd(1, 1, n, dfn[u]);
}

inline void chain(int x, int y, int d) {
    P p;
    while (p = query(1, 1, n, x, y), p.st <= 2 * d) {
        int u = pt[p.nd];
        find(1, 1, n, dfn[u]);
        ans -= get(u); e[u] = 0; ans += get(u);
        upd(1, 1, n, dfn[u]);
    }
    upd(1, 1, n, x, y, d);
}

inline void solve(int u, int v, int d) {
    int lu = 0, lv = 0;
    while (top[u] ^ top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v), swap(lu, lv);
        int f = top[u];
        change(u, lu, u, d);
        if (u ^ f) change(f, son[f], f, d);
        if (dfn[u] > dfn[f] + 1) chain(dfn[f] + 1, dfn[u] - 1, d);
        lu = f; u = fa[f];
    }
    if (dep[u] < dep[v]) swap(u, v), swap(lu, lv);
    if (u == v) change(u, lu, lv, d);
    else {
        change(u, lu, u, d);
        change(v, lv, son[v], d);
        if (dfn[u] > dfn[v] + 1) chain(dfn[v] + 1, dfn[u] - 1, d);
    }
}

int main() {
    io >> n >> q;
    For (i, 1, n) io >> val[i];
    int u, v, d;
    For (i, 1, n - 1) {
        io >> u >> v >> c[i]; es[u].pb(v), es[v].pb(u);
        a[i] = u; b[i] = v;
    }
    dfs0(1, 0);
    For (i, 1, n - 1) {
        u = a[i], v = b[i];
        int p = dep[u]>dep[v]? u: v;
        w[p] = c[i];
        s[u] += w[p]; if (cmax(mx[u], w[p])) e[u] = p;
        s[v] += w[p]; if (cmax(mx[v], w[p])) e[v] = p;
    }
    For (i, 1, n) dd[i] = 2 * mx[i] - s[i], e[i] *= dd[i] > 0, ans += get(i);
    dfs1(1, 1);
    build(1, 1, n);

    printf("%lld\n", ans);
    while (q--) {
        io >> u >> v >> d;
        int f = lca(u, v);
        BIT::upd(dfn[u], d); BIT::upd(dfn[v], d); BIT::upd(dfn[f], -2 * d);
        solve(u, v, d);
        printf("%lld\n", ans);
    }

    return 0;
}
