#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline void mul(int &x, int y) { x = ml(x, y); }

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
	inline IO& operator >> (char &x) {
		while ((c = gc()) < 33 && ~c);
		x = c; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, f[N * N], g[N][N], ans = 1;

namespace DSU {
    int fa[N * N];
    inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }
    inline void merge(int u, int v) {
        u = find(u); v = find(v);
        if (u ^ v) fa[v] = u, mul(f[u], f[v]);
    }
}
using namespace DSU;

inline int id(int i, int j) { return (i - 1) * m + j; }

int main() {
    io >> n >> m;
    char ch;
    For (i, 1, n) For (j, 1, m) {
        io >> ch;
        if (ch == '.') f[id(i, j)] = g[i][j] = 1, fa[id(i, j)] = id(i, j);
    }
    rFor (i, n - 1, 2) {
        For (j, 2, m - 1) if (g[i][j]) {
            if (g[i + 1][j]) merge(id(i, j), id(i + 1, j));
            if (g[i][j + 1]) merge(id(i, j), id(i, j + 1));
        }
        For (j, 2, m - 1) if (g[i][j] && find(id(i, j)) == id(i, j)) add(f[id(i, j)], 1);
    }
    For (i, 1, n * m) if (find(i) == i) mul(ans, f[i]);
    printf("%d", ans);

    return 0;
}
