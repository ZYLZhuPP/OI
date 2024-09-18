#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int n, m, inf, rt[N], fa[N][20], dep[N], a[N], b[N], ans;
vector<int > es[N];

namespace Seg {
    int tot;
    struct Node {
        int l, r, sz;
        Node(int sz = 0): sz(sz) { l = r = 0; }
    } o[N * 20];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline int copy(int p) { o[++tot] = o[p]; return tot; }
    inline void up(int p) { o[p].sz = o[ls].sz + o[rs].sz; }
    inline void upd(int &p, int l, int r, const int &x) {
        if (l > x || r < x) return;
        p = copy(p);
        if (l == r) return void(o[p].sz++);
        M; upd(goL, x); upd(goR, x); up(p);
    }
    inline int query(int p, int l, int r, int q, int i, int j, const int &k) {
        if (l == r) return l;
        int x = o[ls].sz + o[o[q].l].sz - o[o[i].l].sz - o[o[j].l].sz;
        M; return k<=x? query(goL, o[q].l, o[i].l, o[j].l, k): query(goR, o[q].r, o[i].r,  o[j].r, k - x);
    }
}
using namespace Seg;

void dfs(int u, int pre) {
    upd(rt[u] = rt[pre], 1, inf, a[u]);
    fa[u][0] = pre; dep[u] = dep[pre] + 1;
    For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 19, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 19, 0) {
        int fu = fa[u][i], fv = fa[v][i];
        if (fu ^ fv) u = fu, v = fv;
    }
    return fa[u][0];
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1); inf = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, n) a[i] = lower_bound(b + 1, b + inf + 1, a[i]) - b;
    int u, v, k, f;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs(1, 0);
    while (m--) {
        io >> u >> v >> k; u ^= ans;
        f = lca(u, v);
        printf("%d\n", ans = b[query(rt[u], 1, inf, rt[v], rt[f], rt[fa[f][0]], k)]);
    }

    return 0;
}
