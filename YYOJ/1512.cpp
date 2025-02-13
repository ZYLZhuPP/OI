#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5, lgN = 20, Mo = 1e9 + 7;
inline int mo(int x) { return x - (x>=Mo? Mo: x<0? -Mo: 0); }
inline void add(int &x, int y) { x = mo(x + y); }
inline int mul(int x, int y) { return 1ll * x * y % Mo; }

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
} io;

int n, q, u, v, dep[N], fa[lgN][N], m, f[lgN][N], g[lgN][N];
vector<int > es[N];

namespace init {
	void dfsf(int u, int pre) {
		dep[u] = dep[pre] + 1;
		fa[0][u] = pre; For (i, 1, m) fa[i][u] = fa[i - 1][fa[i - 1][u]];
		f[0][u] = es[u].size();
		for (auto &v : es[u]) if (v ^ pre) {
			dfsf(v, u);
			add(f[0][u], f[0][v]);
		}
	}
	
	void dfsg(int u, int pre) {
		For (i, 1, m) f[i][u] = mo(f[i - 1][u] + f[i - 1][fa[i - 1][u]]), g[i][u] = mo(g[i - 1][u] + g[i - 1][fa[i - 1][u]]);
		for (auto &v : es[u]) if (v ^ pre) {
			g[0][v] = mo(f[0][u] + g[0][u] - f[0][v]);
			dfsg(v, u);
		}
	}
	
	int main() {
		m = ceil(log2(n));
		dfsf(1, 0);
		dfsg(1, 0);
	}
}

int solve(int u, int v) {
	int res = 0;
	if (dep[u] > dep[v]) {
		rFor (i, m, 0) if (dep[fa[i][u]] > dep[v]) add(res, f[i][u]), u = fa[i][u];
		add(res, f[0][u]); u = fa[0][u];
	} else if (dep[u] < dep[v]) {
		rFor (i, m, 0) if (dep[u] < dep[fa[i][v]]) add(res, g[i][v]), v = fa[i][v];
		add(res, g[0][v]); v = fa[0][v];
	}
	if (u == v) return res;
	rFor (i, m, 0) if (fa[i][u] ^ fa[i][v]) add(res, mo(f[i][u] + g[i][v])), u = fa[i][u], v = fa[i][v];
	add(res, mo(f[0][u] + g[0][v])); u = fa[0][u]; v = fa[0][v];
	return res;
}

int main() {
	io >> n >> q;
	For (i, 1, n - 1) {
		io >> u >> v;
		es[u].push_back(v);
		es[v].push_back(u);
	}
	
	init::main();
	
	For (i, 1, q) {
		io >> u >> v;
		printf("%d\n", solve(u, v));
	} 
	
	return 0;
} 

