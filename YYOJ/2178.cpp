#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e7 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r = 1; for (; b; mul(a, a), b >>= 1) if (b & 1) mul(r, a); return r; }

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

int n, fac[N], ivf[N];

inline void init() {
	fac[0] = 1;
	For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i);
	ivf[N - 1] = qPow(fac[N - 1], Mo - 2);
	rFor (i, N - 1, 1) ivf[i - 1] = ml(ivf[i], i);
}

inline int C(int n, int m) { return ml(fac[n], ml(ivf[n - m], ivf[m])); }

int main() {
	init();
	io >> n;
	printf("%d", mo(ml(8, C(2 * n, n)) - mo(ml(3, ml(n, n)) + mo(mo(2 * n) + 7))));
	
	return 0; 
}
