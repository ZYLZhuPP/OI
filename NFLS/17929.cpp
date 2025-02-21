#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

struct V {
    ll d, x; int u, v;
    inline V operator + (const V &a) const { return {d + a.d, max(x, d + a.x), u, a.v}; }
    inline bool operator < (const V &a) const {
        bool o1 = d < 0, o2 = a.d < 0;
        return o1^o2? o1: o1? x^a.x? x<a.x: u<a.u: d-x^a.d-a.x? d-x<a.d-a.x: u<a.u;
    }
} f[N];
set<V > se;

int n, ID, w[N], fa[N], pa[N], pos[N], nxt[N];
bool vis[N];
ll s[N], d[N], ans[N];
vector<int > T[N];

namespace Seg {
    struct Node { int l, r; V v; } o[N << 5];
    int rt[N], tot;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].v = o[ls].v + o[rs].v; }
    inline void upd(int &p, int l, int r, int x, const int &u) {
        p = ++tot;
        if (l == r) return o[p].v = {d[u], s[u], 0, 0}, void();
        M; x<=m? upd(goL, x, u): upd(goR, x, u); up(p);
    }
    inline int merge(int p, int q) {
        if (!p || !q) return p | q;
        ls = merge(ls, o[q].l); rs = merge(rs, o[q].r); up(p);
        return p;
    }
}
using namespace Seg;

inline void dfs(int u) {
    assert(pos[u]);
    upd(rt[u], 1, n, pos[u], u);
    for (auto &v : T[u]) dfs(v), rt[u] = merge(rt[u], rt[v]);
    ans[u] = o[rt[u]].v.x + w[u];
}

inline int find(int x) { return pa[x]^x? pa[x] = find(pa[x]): x; }

int main() {
    io >> ID;
    io >> n;
    For (i, 2, n) io >> fa[i], T[fa[i]].pb(i);
    For (i, 1, n) io >> w[i], s[fa[i]] += w[i], pa[i] = i;
    For (i, 1, n) {
        d[i] = s[i] - w[i];
        f[i] = {d[i], s[i], i, i};
        se.insert(f[i]);
    }
    vis[0] = 1;
    int x = 0;
    while (!se.empty()) {
        int u = se.begin()->u, fu = fa[u]; se.erase(se.begin());
        if (vis[fu]) {
            nxt[x] = u;
            while (x ^ f[u].v) vis[x = nxt[x]] = 1;
        } else {
            pa[u] = fu = find(fu);
            se.erase(f[fu]);
            nxt[f[fu].v] = u;
            f[fu] = f[fu] + f[u];
            se.insert(f[fu]);
        }
    }
    x = 0;
    For (i, 1, n) pos[x = nxt[x]] = i;
    dfs(1);
    For (i, 1, n) printf("%lld ", ans[i]);

    return 0;
}
