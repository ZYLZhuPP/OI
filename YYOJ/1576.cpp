#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y) {return x<y? x=y, 1: 0;}
template<class C> inline bool chkmin(C &x, const C &y) {return x>y? x=y, 1: 0;}

const int N = 2005;

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

int n, m, K, l[N], r[N], f[N][N], q[N][N], h[N], t[N], L[N];

void pop(int x, int l) {
	while (h[x] <= t[x] && q[x][h[x]] < l) h[x]++;
}

void push(int x, int r) {
	while (h[x] <= t[x] && f[r][x] - r >= f[q[x][t[x]]][x] - q[x][t[x]]) t[x]--;
	q[x][++t[x]] = r;
}

int main() {
	io >> n >> m >> K;
	for (int i = 1; i <= n; ++i) L[i] = n + 1;
	for (int i = 1; i <= m; ++i) {
		io >> l[i] >> r[i];
		for (int j = l[i]; j <= r[i]; ++j) chkmin(L[j], l[i]);
	}
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= K; ++j) {
			f[i][j] = f[i - 1][j];
			if (L[i] <= i) {
				chkmax(f[i][j], f[L[i] - 1][j - 1] + i - L[i] + 1);
				pop(j - 1, L[i]);
				push(j - 1, i);
				int p = q[j - 1][h[j - 1]];
				chkmax(f[i][j], f[p][j - 1] + i - p);
			}
		}
	} 
	
	printf("%d", f[n][K]);
	
	return 0;
} 
