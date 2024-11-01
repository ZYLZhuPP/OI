#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

int n, m, U[N], V[N], dep[N], pa[N], fa[N][18], op[N], x[N], ans[N], no[N];
vector<int > es[N];
array<int, 3 > mx[N];

inline int find(int x) { return pa[x]^x? pa[x] = find(pa[x]): x; }

inline void dfs0(int u, int pre) {
    dep[u] = dep[pre] + 1; fa[u][0] = pre;
    For (i, 1, 17) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u);
}

inline int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 17, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 17, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

inline int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
inline array<int, 3 > get(int u, int v) { return {dist(u, v), u, v}; }

inline void link(int u, int v) {
    u = find(u); v = find(v); pa[v] = u;
    int u1 = mx[u][1], u2 = mx[u][2], v1 = mx[v][1], v2 = mx[v][2];
    mx[u] = max(max(mx[u], mx[v]), max(max(get(u1, v1), get(u1, v2)), max(get(u2, v1), get(u2, v2))));
}

int main() {
    io >> n >> m;
    For (i, 1, n - 1) io >> U[i] >> V[i], es[U[i]].pb(V[i]), es[V[i]].pb(U[i]);
    dfs0(1, 0);
    For (i, 1, n) pa[i] = i, mx[i] = {0, i, i};
    For (i, 1, m) {
        io >> op[i] >> x[i];
        if (op[i] == 1) no[x[i]] = 1;
    }
    For (i, 1, n - 1) if (!no[i]) link(U[i], V[i]);
    rFor (i, m, 1) {
        if (op[i] == 1) link(U[x[i]], V[x[i]]);
        else ans[i] = max(dist(x[i], mx[find(x[i])][1]), dist(x[i], mx[find(x[i])][2]));
    }
    For (i, 1, m) if (op[i] == 2) printf("%d\n", ans[i]);

    return 0;
}
