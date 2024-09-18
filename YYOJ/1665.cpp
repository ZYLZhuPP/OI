#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e6 + 5, Mo = 998244353;
inline int mo(int &x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline int gmo(int x) { return mo(x); }
inline void add(int &x, const int &y) { mo(x += y); }
inline int mul(const int &x, const int &y) { return 1ll * x * y % Mo; }

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
	inline bool operator ~() {return ~c;}
} io;

int n, p, sum, P, _2, ans, div2;
int inv[N], fac[N], invfac[N];

int C(int n, int m) { return mul(fac[n], mul(invfac[n - m], invfac[m])); }

void init() {
	#define M 3000000
	inv[0] = inv[1] = 1; For (i, 2, M) inv[i] = mul(Mo - Mo / i, inv[Mo % i]);
	fac[0] = invfac[0] = 1; For (i, 1, M) fac[i] = mul(fac[i - 1], i), invfac[i] = mul(invfac[i - 1], inv[i]);
}

int qPow(int a, int b) {
	int res = 1;
	do { if (~b&1 || (res = mul(res, a))) a = mul(a, a); } while(b >>= 1);
	return res;
}

int main() {
	init();
	io >> n >> p;
	sum = qPow(p + 2, n); sum = qPow(sum, Mo - 2);
	div2 = qPow(2, Mo - 2); _2 = qPow(2, n - 1);
	
	P = 1;
	For (i, 0, n - 1) {
		int x = ((n - i) & 1)? _2: gmo(_2 - mul(C(n - i, (n - i) / 2), div2));
		int res = mul(mul(i + 1, P), mul(C(n, i), x));
		add(ans, res);
		P = mul(P, p);
		_2 = mul(_2, div2);
	}
	
	ans = mul(ans, sum);
	
	printf("%d", ans);
	
	return 0;
} 
