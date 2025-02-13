#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e4 + 5, Mo = 1e9 + 9, inf = 1e9;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, m, C, fa[N], sz[N], ans;
vector<array<int, 3 > > a[2][N], b[2][N], es;

struct V {
    int t, p, s;
    bool operator < (const V &a) const { return s < a.s; }
    V operator + (const V &a) const { return {a.t, p, s + a.s}; }
    V& operator += (const V &a) { return *this = *this + a; }
};

namespace Seg {
    struct Node { int l, r; V mn, Mn, t, T; } o[N * 500];
    int tot, A[N], B[N];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void copy(int &p) { o[++tot] = o[p]; p = tot; }
    inline void up(int p) { o[p].mn = min(o[ls].mn, o[rs].mn); o[p].Mn = min(o[ls].Mn, o[rs].Mn); }
    inline void mark(int &p, const V &v, const V &h) { copy(p); cmin(o[p].Mn, o[p].mn + h); cmin(o[p].T, o[p].t + h); o[p].mn += v; o[p].t += v; }
    inline void down(int p) { if (o[p].t.t) mark(ls, o[p].t, o[p].T), mark(rs, o[p].t, o[p].T), o[p].t = o[p].T = {0, 0, 0}; }
    inline void build(int &p, int l, int r) {
        copy(p); o[p].mn = o[p].Mn = {0, l, inf}; o[p].t = o[p].T = {0, 0, 0};        
        if (l == r) return;
        M; build(goL); build(goR);
    }
    inline void upd(int &p, int l, int r, int x, int y, const V &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, d, d);
        copy(p); down(p); M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline V query(int &p, int l, int r, int x, int y) {
        if (l > y || r < x) return {0, 0, inf};
        if (x <= l && r <= y) return o[p].Mn;
        copy(p); down(p); M; return min(query(goL, x, y), query(goR, x, y));
    }
}
using namespace Seg;

inline void add(int x, int X, int y, int Y, int w) {
    if (x > X || y > Y) return;
    a[0][x].pb({y, Y, w}); a[1][X + 1].pb({y, Y, -w});
    b[0][Y].pb({x, X, w}); b[1][y - 1].pb({x, X, -w});
}

inline void Add(int u, int v, int w) {
    if (u > v) swap(u, v);
    add(1, u - 1, u, v - 1, w);
    add(u, v - 1, v, n, w);
}

inline void solve(int l, int r) {
    if (l == r) return;
    V x = min(query(A[l - 1], 1, n, l, r - 1), query(B[r], 1, n, l, r - 1));
    int m = x.p;
    es.pb({-x.s, l, r});
    solve(l, m); solve(m + 1, r);
}

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

int main() {
    io >> n >> m >> C;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, Add(u, v, w);
    a[1][1].pb({1, n, -inf}); b[1][n].pb({1, n, -inf});
    build(A[0], 1, n);
    For (i, 1, n) {
        A[i] = A[i - 1];
        For (o, 0, 1) for (auto &[l, r, x] : a[o][i]) upd(A[i], 1, n, l, r, {i, 0, x});
    }
    build(B[n + 1], 1, n);
    rFor (i, n, 1) {
        B[i] = B[i + 1];
        For (o, 0, 1) for (auto &[l, r, x] : b[o][i]) upd(B[i], 1, n, l, r, {i, 0, x});
    }
    solve(1, n);
    sort(es.begin(), es.end());
    For (i, 1, n) fa[i] = i, sz[i] = 1;
    for (auto [w, u, v] : es) {
        u = find(u); v = find(v);
        add(ans, ml(-w, ml(sz[u], sz[v])));
        fa[v] = u; sz[u] += sz[v];
    }
    add(ans, ans); add(ans, ml(ml(2, C), ml(n, n - 1)));
    printf("%d", ans);

    return 0;
}
