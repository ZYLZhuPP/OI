#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e3 + 5, Mo = 1e4 + 7;
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int a, b, k, n, m, inv[N], fac[N], ivf[N];

void init() {
    inv[1] = 1;
    For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1;
    For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
}

inline int C(int n, int m) { return ml(fac[n], ml(ivf[n - m], ivf[m])); }

int main() {
    init();
    io >> a >> b >> k >> n >> m;
    printf("%d", ml(ml(qPow(a, n), qPow(b, m)), C(k, n)));

    return 0;
}
