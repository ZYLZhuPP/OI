#include<bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5;

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

int n, m, f[N], g[N], w[N]; 

int main() {
	io >> n >> m;
	for (int i = 1; i <= n; i++)
		io >> w[i];
	
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= w[i]; j--) 
			(f[j] += f[j - w[i]])%=10; 
	} 
	for (int i = 1; i <= n; i++) {
		memcpy(g, f, sizeof f);
		for (int j = w[i]; j <= m; j++) 
			(g[j] -= g[j - w[i]]-10)%=10;
		for (int j = 1; j <= m; j++) 
			printf("%d", g[j]);
		puts("");
	}
	
	return 0;
}
