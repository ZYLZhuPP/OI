#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2005, Mo = 1e9 + 9;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline void mul(int &x, int y) { x = ml(x, y); }

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
    inline bool operator ~ () { return ~c; }
} io;

int n, k, a[N], b[N], c[N], f[N][N], ans;
int inv[N], fac[N], ivf[N];

inline int C(int n, int m) { return ml(fac[n], ml(ivf[n - m], ivf[m])); }

void init() {
	inv[1] = 1;
	For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
	fac[0] = ivf[0] = 1;
	For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
}

int main() {
	init();
	io >> n >> k; k = (n + k) / 2;
	For (i, 1, n) io >> a[i];
	For (i, 1, n) io >> b[i];
	sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
	For (i, 1, n) {
		c[i] = c[i - 1];
		while (c[i] < n && a[i] > b[c[i] + 1]) c[i]++;
	}
	For (i, 0, n) f[i][0] = 1;
	For (i, 1, n) For (j, 1, i) f[i][j] = mo(f[i - 1][j] + ml(f[i - 1][j - 1], c[i] - j + 1));
	For (i, k, n) add(ans, ((i-k)&1? -1: 1) * ml(C(i, k), ml(f[n][i], fac[n - i])));
	printf("%d", ans);
	
	return 0;
}
