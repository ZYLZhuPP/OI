#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y) { return x<=y? x=y, 1: 0; }

const int N = 105;

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
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int n, h[2*N], ans, f[2*N][2*N];

int main() {
	io >> n;
	for (int i = 1; i <= n; i++)
		io >> h[i];
	for (int i = n+1; i <= 2*n + 1; i++)
		h[i] = h[i - n];
		
	for (int i = 1; i < n; i++)
		for (int j = 1; j+i <= 2*n; j++) {
			int l = j, r = i + j;
			for (int k = l; k < r; k++)
				chkmax(f[l][r], f[l][k] + f[k+1][r] + h[l]*h[k+1]*h[r+1]);
		}
	for(int i = 1; i <= n; i++)
		chkmax(ans, f[i][i+n-1]);
		
	printf("%d", ans); 
	return 0;
} 
