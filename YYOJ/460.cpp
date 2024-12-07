#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

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

int n, ans, f[N];

int main() {
	io >> n;
	
	for (int j = 2; j <= n; j++) {
		f[j]++;
		for (int i = 2; i*j <= n; i++)
			f[i*j] += f[i];
	} 
	
	for (int i = 2; i <= n; i++)
		ans ^= f[i];
	
	printf("%d", ans); 
	return 0;
}
