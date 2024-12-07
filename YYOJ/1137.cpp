#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y) { return x<=y? x=y, 1: 0; }

typedef long long ll;

const int N = 305, Sta = (1<<8) + 5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline IO& operator >> (char &x){
		while(c<33) c=gc(); x=c; c=gc();
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

ll n, k, a[N], to[Sta], w[Sta], f[N][N][Sta], ans;

int main() {
	io >> n >> k;
	for (int i = 1; i <= n; i++) {
		char c;
		io >> c;
		a[i] = c ^ 48;
	}
	for (int i = 0; i < 1<<k; i++) 
		io >> to[i] >> w[i];
	
	memset(f, 192, sizeof f);
	for (int i = 1; i <= n; i++) f[i][i][a[i]] = 0;
	for (int d = 1; d < n; d++) {
		for (int i = 1; i+d <= n; i++) {
			int j = i + d;
			int t = d % (k-1); t += !t*(k-1); 
			for (int p = j - 1; p >= i; p -= k-1) {
				for (int s = 0; s < 1<<t; s++) {
					chkmax(f[i][j][s<<1], f[i][p][s] + f[p+1][j][0]);
					chkmax(f[i][j][s<<1 | 1], f[i][p][s] + f[p+1][j][1]);
				}
			}
			if (t == k-1) {
				ll g[2] = {-1, -1}; 
				for (int s = 0; s < 1<<k; s++)
					chkmax(g[to[s]], f[i][j][s] + w[s]);
				f[i][j][0] = g[0];
				f[i][j][1] = g[1];
			}	
		}
	}
	
	for (int s = 0; s < 1<<(k-1); s++)
		chkmax(ans, f[1][n][s]);
	printf("%lld", ans);
	return 0;
}
