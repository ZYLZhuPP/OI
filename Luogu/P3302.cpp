#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 8e4 + 5;

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

int testcase, n, m, T, B, w[N], b[N], ans, rt[N];
int fa[N][20], dep[N];
vector<int > es[N];

namespace DSU {
    int pa[N], sz[N];
    inline int find(int u) { return u^pa[u]? pa[u] = find(pa[u]): u; }
    inline void merge(int u, int v) { pa[v] = u; sz[u] += sz[v]; }
}
using namespace DSU;

namespace Seg {
    int tot;
    struct Node {
        int l, r, sz;
        Node() { l = r = sz = 0; }
    } o[N << 5];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline int copy(const int &p) { o[++tot] = o[p]; return tot; }
    inline void up(const int &p) { o[p].sz = o[ls].sz + o[rs].sz; }
    inline void upd(int &p, int l, int r, const int &x) {
        if (l > x || r < x) return;
        p = copy(p);
        if (l == r) return void(o[p].sz++);
        M; upd(goL, x); upd(goR, x); up(p);
    }
    inline int query(int p, int l, int r, int q, int f, int ff, const int &k) {
        if (l == r) return l;
        int x = o[ls].sz + o[o[q].l].sz - o[o[f].l].sz - o[o[ff].l].sz;
        M; return k<=x? query(goL, o[q].l, o[f].l, o[ff].l, k): query(goR, o[q].r, o[f].r, o[ff].r, k - x);
    }
}
using namespace Seg;

void dfs(int u, int pre) {
    fa[u][0] = pre; dep[u] = dep[pre] + 1;
    For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    if (rt[u]) tot = rt[u] - 1;
    upd(rt[u] = rt[pre], 1, B, w[u]);
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 19, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 19, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int main() {
    io >> testcase;
    io >> n >> m >> T;
    For (i, 1, n) io >> w[i], b[i] = w[i], pa[i] = i, sz[i] = 1;
    sort(b + 1, b + n + 1); B = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, n) w[i] = lower_bound(b + 1, b + B + 1, w[i]) - b;
    int u, v, k;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (i, 1, n) if (!rt[i]) dfs(i, 0);

    char op[3];
    while (T--) {
        scanf("%s", op);
        if (op[0] == 'Q') {
            io >> u >> v >> k;
            u ^= ans; v ^= ans; k ^= ans;
            int f = lca(u, v);
            printf("%d\n", ans = b[query(rt[u], 1, B, rt[v], rt[f], rt[fa[f][0]], k)]);
        } else if (op[0] == 'L') {
            io >> u >> v;
            u ^= ans; v ^= ans;
            es[u].pb(v); es[v].pb(u);
            int fu = find(u), fv = find(v);
            if (sz[fv] > sz[fu]) swap(u, v), swap(fu, fv);
            merge(fu, fv);
            dfs(v, u);
        }
    }

    return 0;
}
