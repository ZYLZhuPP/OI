#include<bits/stdc++.h> 
using namespace std;

typedef long long ll;

const int N = 2e3 + 5;

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

int T, n, m;
ll a[N], q[2 * N][N], h[2 * N], t[2 * N], f[N][N], ans, s[N];

ll Y(int k, int i) {
	int j = i + k - n;
	return f[i][j] - s[i] + a[i] * i;
}

void upd(int k, int i) {
	while (h[k] < t[k] && 1ll * i * (a[q[k][t[k]]] - a[q[k][t[k] - 1]]) > Y(k, q[k][t[k]]) - Y(k, q[k][t[k] - 1])) t[k]--;
	int j = i + k - n;
	if (h[k] <= t[k]) f[i][j] = s[i] + Y(k, q[k][t[k]]) - a[q[k][t[k]]] * i;
	f[i][j] = max(f[i][j], f[i - 1][j]);
	while (h[k] < t[k] && 1ll * (Y(k, i) - Y(k, q[k][t[k]])) * (a[q[k][t[k]]] - a[q[k][t[k] - 1]]) > 1ll * (Y(k, q[k][t[k]]) - Y(k, q[k][t[k] - 1])) * (a[i] - a[q[k][t[k]]])) t[k]--;
	q[k][++t[k]] = i;
}

void init() {
	memset(f, 0, sizeof(f));
	memset(h, 0, sizeof(h));
	memset(t, -1, sizeof(t));
}

int main() {
	io >> T;
	while (T--) {
		init();
		io >> n >> m;
		for (int i = 1; i <= n; ++i) io >> a[i];
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
		
		q[n][++t[n]] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= n - m; ++j) {
				upd(j - i + n, i);
			}
		}
		
		printf("%lld\n", s[n] - f[n][n - m]);
	}
	
	return 0;
}

