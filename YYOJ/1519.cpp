#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5, D = 2e3 + 5;
const ll Mo = 1e9 + 7;

template<class C> inline bool chkmax(C &x, const C &y) {return x<y? x=y, 1: 0;} 

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

ll n, m, d, d1, d2, a, b, cnt, l, r, f[D][D], ans;
char s[N];

int main() {
	io >> n >> m; d = n - m;
	scanf("%s", s);
	
	for (int i = 0; i < m; i++) {
		if (s[i] == '(') l++, cnt++;
		else r++, cnt--;
		chkmax(d1, -cnt);
	}
	
	cnt = 0;
	for (int i = m-1; i >= 0; i--) {
		if (s[i] == ')') cnt++;
		else cnt--;
		chkmax(d2, -cnt);
	}
	
	a = (d + r - l) / 2;
	b = (d - r + l) / 2;
	
	if (a + b < d || a < 0 || b < 0) {
		puts("0");
		return 0;
	}
	
	f[0][0] = 1;
	for (int i = 1; i <= d; i++) {
		f[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			f[i][j] = (f[i-1][j] + f[i][j-1]) % Mo;
		}
	}
	
	for (int i = 0; i <= a; i++) {
		for (int j = 0; j <= i && j <= b; j++) if (i - j >= d1) {
			int i_ = a - i, j_ = b - j;
			if (j_ - i_ >= d2) 
				(ans += f[i][j] * f[j_][i_] % Mo) %= Mo;
		}
	}
	
	printf("%lld", ans);
	
	return 0;
} 
