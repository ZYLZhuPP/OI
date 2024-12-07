#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y){ return x<y? x=y, 1: 0;}

const int N = 1e4 + 5;

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

int n, m, l, a[N], f[N], len, ans[N];

int main() {
	io >> n;
	for (int i = 1; i <= n; i++) 
		io >> a[i];
	
	for (int i = n; i >= 1; i--) {
		f[i] = 1;
		for (int j = n; j > i; j--)
			if (a[j] > a[i]) 
				chkmax(f[i], f[j] + 1);
		chkmax(len, f[i]);
	} 
	
	io >> m;
	while (m--) {
		io >> l;
		if (l > len) puts("Impossible");
		else {
			int x = 0, t = 0;
			for (int i = 1; i <= n && t < l; i++) 
				if (f[i] >= l-t && a[i] > a[x]) {
					ans[++t] = a[i];
					x = i;
				} 
			for (int i = 1; i <= t; i++)
				printf("%d ", ans[i]);
			puts("");
		}
	}
	
	return 0;
} 
