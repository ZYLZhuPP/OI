#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, a[N], f[N][4], g[N][4];
vector<int > es[N];

inline void dfs(int u, int pre) {
    f[u][0] = 1; f[u][1] = f[u][2] = a[u]; f[u][3] = ml(a[u], a[u]);
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        For (i, 0, 3) For (j, 0, 3) {
            int x = ml(f[u][i], f[v][j]);
            if (j == 3) add(g[u][i], x);
            if (!(i & j)) add(g[u][i | j], x);
        }
        For (i, 0, 3) f[u][i] = g[u][i], g[u][i] = 0;
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs(1, 0);
    printf("%d", f[1][3]);

    return 0;
}
