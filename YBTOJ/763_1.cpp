#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, M = 1e6 + 5, Mo = 1e9 + 7;
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

int n, k, h[N], f[N][N], g[N];
int ls[N], rs[N], stk[N], top;
int inv[M], fac[M], ivf[M];

void init() {
    inv[0] = inv[1] = 1;
    For (i, 2, M - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1;
    For (i, 1, M - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
}

inline int C(int n, int m) {
    return n>=m? ml(fac[n], ml(ivf[n - m], ivf[m])): 0;
}

int solve(int u, int pre) {
    int W = 1, H = h[u] - h[pre];
    if (ls[u]) W += solve(ls[u], u);
    if (rs[u]) W += solve(rs[u], u);
    memset(g, 0, sizeof g);
    For (i, 0, k) For (j, 0, k - i) add(g[i + j], ml(f[ls[u]][i], f[rs[u]][j]));
    For (i, 0, k) For (j, 0, i) add(f[u][i], ml(ml(g[i - j], fac[j]), ml(C(H, j), C(W - (i - j), j))));
    return W;
}

int main() {
    init();
    io >> n >> k;
    For (i, 1, n) {
        io >> h[i];
        while (top && h[stk[top]] > h[i]) top--;
        ls[i] = rs[stk[top]]; rs[stk[top]] = i;
        stk[++top] = i;
    }
    f[0][0] = 1;
    solve(stk[1], 0);
    printf("%d", f[stk[1]][k]);

    return 0;
}
