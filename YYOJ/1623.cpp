#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 505, M = 512;

struct IO {
	char c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

struct Big {
	static const int Siz = 60;
	static const ll B = 1e17;
	ll a[Siz], t;
	
	Big() {memset(a, 0, sizeof(a)); t = 0;}
	Big(const Big &x) {
		memset(a, 0, sizeof(a)); t = x.t;
		for (int i = 1; i <= t; ++i) a[i] = x.a[i];
	}
	Big (const ll &x) {
		memset(a, 0, sizeof(a)); t = 0;
		ll o = x;
		while (o) a[++t] = o % B, o /= B;
	}
	
	Big& operator += (const Big &x) {
	    t = max(t, x.t);
		for (int i = 1; i <= t; ++i) {
			a[i] += x.a[i];
			if (a[i] >= B) a[i + 1]++, a[i] -= B;
		}
		if (a[t + 1]) t++;
		return *this;
	}
	
	Big operator * (const ll &x) const {
		Big res; if (!x) return res;
		ll n = t, up = 0;
		for (int i = 1; i <= n; ++i) {
			ll m = a[i] * x + up;
			up = m / B; res.a[i] = m % B;
		}
		while (up) res.a[++n] = up % B, up /= B;
		res.t = n;
		return res;
	}
	
	void print() const {
		if (!t) {puts("0"); return;}
		printf("%lld", a[t]);
		for (int i = t - 1; i >= 1; --i) printf("%017lld", a[i]);
		puts("");
	}
} f[N][M], S[N][M];

bool vis[N][M];
ll n, m, a, b, d[N], K, STA;

int main() {
	io >> n >> m >> K; STA = 1 << K;
	for (int i = 1; i <= m; ++i) {
		io >> a >> b; a--; b--;
		d[b] |= 1 << a;
	}
	
	f[0][0] = 1;
	for (int i = 0; i < n; ++i) {
	    for (int s = 0; s < STA; ++s) {
	        for (int j = 0; j < K; ++j) if (!(s & d[j])) {
	            int s_ = s | (1 << j);
	            f[i + 1][s_] += f[i][s];
	            S[i + 1][s_] += S[i][s] * 10;
	            S[i + 1][s_] += f[i][s] * (j + 1);
	        }
	    }
	}
	
	Big ans1, ans2;
	for (int i = 0; i < STA; ++i) ans1 += f[n][i], ans2 += S[n][i];
	
	ans1.print();
	ans2.print();
	
	return 0;
} 
