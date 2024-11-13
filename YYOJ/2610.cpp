#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e18;
const int N = 5e5 + 5;
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

int n, rt[N], w[N];
vector<int > es[N];
ll f[N], g[N], c1, c2, res;

namespace Seg {
    struct Node {
        int l, r; ll t, a, b;
        Node() { l = r = t = 0; a = b = -INF; }
    } o[N << 5];
    int tot;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].a = max(o[ls].a, o[rs].a); o[p].b = max(o[ls].b, o[rs].b); }
    inline void upd(int &p, int l, int r, int x) {
        p = ++tot;
        if (l == r) return o[p].a = x, o[p].b = 0, void();
        M; x<=m? upd(goL, x): upd(goR, x); up(p);
    }
    inline void mark(int p, ll d) { if (p) o[p].a += d, o[p].b += d, o[p].t += d; }
    inline void down(int p) { if (o[p].t) mark(ls, o[p].t), mark(rs, o[p].t), o[p].t = 0; }
    inline void merge(int &p, int l, int r, int q, int u, int v) {
        if (!p && !q) return;
        if (!p || !q) {
            if (!q) {
                cmax(res, o[p].b + c2); cmax(c1, o[p].a);
                return mark(p, f[v]);
            } else {
                cmax(res, o[q].b + c1); cmax(c2, o[q].a);
                return mark(p = q, g[u]);
            }
        }
        if (l == r) {
            cmax(res, max({o[p].b + c2, o[q].b + c1, o[p].b + o[q].b + l}));
            cmax(c1, o[p].a); cmax(c2, o[q].a);
            o[p].b = max(o[p].b + f[v], o[q].b + g[u]);
            o[p].a = o[p].b + l;
            return;
        }
        M; down(p); down(q); merge(goL, o[q].l, u, v); merge(goR, o[q].r, u, v); up(p);
    }
}
using namespace Seg;

inline void dfs(int u, int pre) {
    f[u] = g[u] = 0; upd(rt[u], 1, 1e9, w[u]);
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        c1 = c2 = res = -INF;
        merge(rt[u], 1, 1e9, rt[v], u, v);
        f[u] = max(res, f[u] + f[v]);
        g[u] += f[v];
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> w[i];
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs(1, 0);
    printf("%lld", max(f[1], g[1]));

    return 0;
}
