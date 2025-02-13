#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5005, Mo = 998244853;
inline int mo(int x) { return x - (x>=Mo? Mo: x<0? -Mo: 0); }
inline void add(int &x, int y) { x = mo(x + y); }
inline int mul(int x, int y) { return 1ll * x * y % Mo; }

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
} io;

int n, k, x, a[N], S[N][N], inv3, _3, dwn, ans;

int qPow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

void init() {
	#define M 5000
	S[0][0] = 1; For (i, 1, M) For (j, 1, i) S[i][j] = mo(S[i - 1][j - 1] + mul(S[i - 1][j], j));
	inv3 = qPow(3, Mo - 2);
}

int main() {
	init();
	io >> n >> k;
	For (i, 0, k) {
		io >> x;
		For (j, 0, i) add(a[j], mul(x, S[i][j])); 
	}
	
	_3 = qPow(3, n); dwn = 1;
	For (i, 0, k) {
		add(ans, mul(a[i], mul(dwn, _3)));
		_3 = mul(_3, inv3);
		dwn = mul(dwn, n - i);
	}
	
	printf("%d", ans);
	
	return 0;
} 
