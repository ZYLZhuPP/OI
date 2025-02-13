#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e7 + 5;
const int Mo = 998244353;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, m;
int ans, x, inv[N], S;

void init() {
	inv[0] = inv[1] = 1;
	for (int i = 2; i < N; ++i) inv[i] = (ll)(Mo - Mo / i) * inv[Mo % i] % Mo;
	for (int i = 2; i <= n * m + 1; ++i) S = (ll)(S + inv[i]) % Mo;
}

int main() {
	io >> n >> m;
	init();
	for (int i = 1; i <= n; ++i) {
		io >> x;
		ans = ((ll)ans + (ll)x * m) % Mo;
	}
	
	printf("%lld", ((ll)ans * ((ll)n * m - S + Mo) % Mo) * inv[n * m] % Mo);
	
	return 0;
}

