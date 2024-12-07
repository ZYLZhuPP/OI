#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;
const ll Mo = 998244353;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, v;
ll ans, inv[N], fac[N], invfac[N];
vector<int > es[N];

void dfs(int u, int d) {
	if (u) ans = (ans + fac[n] * invfac[d] % Mo) % Mo;
	for (auto &v : es[u]) {
		dfs(v, d + 1); 
	} 
}

void init() {
	inv[0] = inv[1] = 1;
	for (int i = 2; i < N; ++i) inv[i] = (Mo - Mo / i) * inv[Mo % i] % Mo;
	fac[0] = invfac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % Mo, invfac[i] = invfac[i - 1] * inv[i] % Mo;
}

int main() {
	init();
	io >> n;
	for (int i = 1; i <= n; ++i) {
		io >> v; if (!~v) v = 0;
		es[v].push_back(i);
	}
	
	dfs(0, 0);
	
	printf("%lld", ans * invfac[n] % Mo);
	
	return 0;
} 
