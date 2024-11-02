#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, inf = 1e9;
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

int n, a[N], w[N], sz[N], f[N][2][N], g[2][N], ans = 2e9;
vector<int > es[N];

inline void dfs(int u, int pre) {
    if (es[u].size() == (bool)pre) {
        sz[u] = 1;
        f[u][0][1] = f[u][1][0] = 0;
        f[u][0][0] = a[u];
        return;
    }
    f[u][0][0] = f[u][1][0] = 0;
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u);
    for (auto &v : es[u]) if (v ^ pre) {
        For (i, 0, 1) For (j, 0, sz[u] + sz[v]) g[i][j] = inf;
        For (i, 0, 1) For (j, 0, sz[u]) For (k, 0, 1 - i) For (l, 0, sz[v]) cmin(g[i + k][j + l], f[u][i][j] + f[v][k][l]);
        sz[u] += sz[v];
        For (i, 0, 1) For (j, 0, sz[u]) f[u][i][j] = g[i][j];
    }
    int s = 0; g[0][0] = 0;
    for (auto &v : es[u]) if (v ^ pre) {
        For (i, 0, s + sz[v]) g[1][i] = inf;
        For (i, 0, s) For (j, 0, sz[v]) cmin(g[1][i + j], g[0][i] + f[v][1][j]);
        s += sz[v];
        For (i, 0, s) g[0][i] = g[1][i];
    }
    For (i, 0, 1) For (j, 0, sz[u]) cmin(f[u][i][j], a[u] + g[1][j]);
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) io >> w[i];
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    memset(f, 63, sizeof f);
    dfs(1, 0);
    For (i, 0, n) cmin(ans, f[1][1][i] + w[i]);
    printf("%d", ans);

    return 0;
}
