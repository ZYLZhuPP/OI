#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2005, Mo = 998244353;
inline int mo(int x) { return x -= x >= Mo ? Mo : x < 0 ? -Mo : 0; }
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
	inline bool operator ~ () { return ~c; }
} io;

int n, m, inv[N], fac[N], ivf[N], __2[N], ans, g[N][N], f[N];

inline int qPow(int a, int b) {
	int r = 1;
	while (b) {
		if (b & 1) mul(r, a);
		mul(a, a);
		b >>= 1;
	}
	return r;
}

void init() {
	inv[0] = inv[1] = 1;
	For (i, 2, n) inv[i] = ml((Mo - Mo / i), inv[Mo % i]);
	fac[0] = ivf[0] = 1;
	For (i, 1, n) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
	__2[0] = 2;
	For (i, 1, n) __2[i] = ml(__2[i - 1], __2[i - 1]);
}

inline int C(int n, int m) {
	return ml(fac[n], ml(ivf[n - m], ivf[m]));
}

int main() {
	io >> n >> m;
	init();
	if (m == 0) ans = __2[n];
	else if (m == 1) {
		int d = 1;
		For (i, 0, n) {
			add(ans, d * ml(C(n, i), __2[n - i]));
			d = -d;
		}
	} else {
        g[0][0] = 1;
        For (i, 1, n) {
            g[i][0] = 1;
            For (j, 1, i) g[i][j] = mo(g[i - 1][j - 1] + ml(j + 1, g[i - 1][j]));
        }
        For (i, 0, n) {
            int _2 = qPow(2, n - i), t = 1;
            For (j, 0, i) {
                add(f[i], ml(g[i][j], t));
                mul(t, _2);
            }
        }
        int d = 1;
		For (i, 0, n) {
			add(ans, d * ml(C(n, i), ml(f[i], __2[n - i])));
			d = -d;
		}
	}
	printf("%d", ml(ans, 499122177));
	
	return 0;
}

