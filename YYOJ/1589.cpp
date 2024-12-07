#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 5e5 + 5;
const ll Mo = 998244353;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int T, I;
ll ans, s[10], _10[N], f[N], g[N], sum[N];
char a[N], b[N];

ll get(char* st) {
	memset(s, 0, sizeof(s));
	ll res = 0;
	
	int l = strlen(st);
	sum[0] = 0;
	for (int i = l - 1; i >= 0; --i) sum[l - i] = (sum[l - i - 1] + (st[i] ^ 48) * _10[l - i - 1] % Mo) % Mo;
	for (int i = 0; i < l; ++i) {
		int x = st[i] ^ 48, p = l - i;
		
		for (int j = 9; j > 0; --j) res += s[j] * j * f[p - 1] * x;
		res %= Mo;
		
		res += g[p - 1] * x;
		res += f[p - 1] * x * (x - 1) / 2;
		res %= Mo;
		for (int j = 1; j <= x; ++j) res += s[j] * j * _10[p - 1], res %= Mo;
		for (int j = x + 1; j <= 9; ++j) {
			res += s[j] * x * _10[p - 1];
			res += s[j] * (sum[p - 1] + 1);
		    res %= Mo;
		}
		s[x]++;
		
		res %= Mo;
	} 
	
	return res;
}

void init() {
	_10[0] = 1;
	for (int i = 1; i < N; ++i) {
		_10[i] = _10[i - 1] * 10 % Mo;
		f[i] = i * _10[i - 1] % Mo;
		g[i] = (g[i - 1] * 10 + f[i - 1] * 45) % Mo;
	}
}

int main() {
	init();
	io >> T >> I;
	while (T--) {
		scanf("%s%s", a, b);
		ll ans = get(b) - get(a) + Mo;
		memset(s, 0, sizeof(s));
		int l = strlen(a);
		for (int i = l - 1; i >= 0; --i) {
			int x = a[i] ^ 48;
			for (int j = 0; j < x; ++j) ans += s[j];
			s[x]++; 
		} 
		printf("%lld\n", ans % Mo);
	}
	
	return 0;
} 
