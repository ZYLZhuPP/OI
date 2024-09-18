#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;

struct T{
	int b,e;
	bool operator < (const T X) const{
		return e<X.e;
	}
}a[N];

int n,f[N],ans;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^'-')) f=-1;
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int main(){
	io>>n;
	for(int i=0; i<n; i++) io>>a[i].b>>a[i].e, f[i]=1;
	sort(a, a+n);
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++) if(a[j].e<=a[i].b) f[i]=max(f[i], f[j]+1);
		ans=max(ans, f[i]);
	}
	printf("%d", ans);
	return 0;
} 
