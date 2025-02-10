#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int n, sz[N], f[N], g[N], h[N], ans, inv[N];
vector<int > es[N];

inline void dfs(int u, int pre) {
    sz[u] = 1;
    int x = 1;
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u), sz[u] += sz[v], h[v] = x, mul(x, f[v]);
    if (sz[u] == 1) { f[u] = g[u] = 1; return; }
    g[u] = x;
    reverse(es[u].begin(), es[u].end());
    x = 1;
    for (auto &v : es[u]) if (v ^ pre) add(g[u], ml(ml(g[v], inv[sz[u] - sz[v]]), ml(h[v], x))), mul(x, f[v]);
    f[u] = ml(g[u], inv[sz[u]]);
}

int main() {
    io >> n;
    inv[1] = 1; For (i, 2, n) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs(1, 0);
    ans = 1; For (i, 1, n - 1) mul(ans, i);
    for (auto &u : es[1]) mul(ans, f[u]);
    printf("%d", ans);

    return 0;
}
