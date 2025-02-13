#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 5e6 + 5;
int Mo;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
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

int n, k, m, fac[N], ivf[N], inv[N], a[N], ans;

int main() {
    io >> n >> Mo >> k;
    fac[0] = ivf[0] = 1;
    For (i, 1, n) io >> a[i], fac[i] = ml(fac[i - 1], a[i]);
    ivf[n] = qPow(fac[n], Mo - 2);
    rFor (i, n - 1, 1) ivf[i] = ml(ivf[i + 1], a[i + 1]);
    For (i, 1, n) inv[i] = ml(ivf[i], fac[i - 1]);
    m = k;
    For (i, 1, n) add(ans, ml(m, inv[i])), mul(m, k);
    printf("%d", ans);

    return 0;
}
