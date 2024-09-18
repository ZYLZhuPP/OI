#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1005, M = 6, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }

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
	inline bool operator ~ () { return ~c; }
} io;

int n, K, u, v, siz[N], ans[N * M], f[N][M][N * M], g[M][N * M];
vector<int > es[N];

void dfs(int u, int pre) {
    siz[u] = 1;
    For (i, 1, K) f[u][i][0] = 1;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        For (i, 0, K) For (j, 0, siz[u] * K - i)
            g[i][j] = f[u][i][j], f[u][i][j] = 0;
        For (i, 0, K) For (j, 0, siz[u] * K - i) if (g[i][j]) {
            For (p, 0, K) For (q, 0, siz[v] * K - i) if (f[v][p][q]) {
                int j_ = j + (p + q), i_ = max(i + j + q, j_) - j_;
                add(f[u][i_][j_], ml(g[i][j], f[v][p][q]));
            }
        }
        siz[u] += siz[v];
    }
}

int main() {
    io >> n >> K;
    For (i, 1, n - 1) io >> u >> v, es[u].push_back(v), es[v].push_back(u);
    
    dfs(1, 0);

    For (i, 0, K) For (j, 0, siz[1] * K - i) add(ans[i + j], f[1][i][j]);
    For (i, 1, n * K) printf("%d\n", ans[i]);

    return 0;
}
