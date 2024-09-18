#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2005;
const ll Mo = 998244353;

struct IO {
	char c, f;
	#define gc() getchar()
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

ll n, k, f[2*N][N], g[N], ans;
ll inv[N], fac[N];

void init() {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = (fac[i - 1] * i) % Mo;
}

int main() {
	io >> n >> k;
	init();
	
	for (int i = 1; i <= 2*n; i++) f[i][1] = i;
	for (int j = 2; j <= n; j++) {
		ll s = 0;
		for (int i = 2*j - 1; i <= 2*n; i++) {
			s = (s + f[i - 2][j - 1]) % Mo;
			f[i][j] = s;
		}
	}
	
	g[0] = 1;
	for (int i = 1; i <= min(n, 2*k); i++) {
		int l = (n - i) / (2*k) + 1, j = i + (l - 1) * (2*k);
		int s = (l - 1) * 2 + (i > k) + (j <= n - k);
		for (int k = n; k >= 1; k--) {
			for (int p = 1; p <= l; p++) if (k >= p){
				g[k] = (g[k] + f[s][p] * g[k - p]) % Mo;
			}
		}
	}
	
	for (int i = 0; i <= n; i++) {
		ll w = (g[i] * fac[n - i]) % Mo;
		ans = (ans + ((i&1)? -1: 1) * w + Mo) % Mo;
	}
	
	printf("%lld", ans);
	
	return 0;
} 
