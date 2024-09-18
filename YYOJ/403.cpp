#include<bits/stdc++.h>
using namespace std;

typedef double DB;

const int N=2e5+5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^'-')) f=-1;
		for(x=0; isdigit(c); c=gc()) x=x*10+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct P{
	DB l,r;
	bool operator < (const P X) const{
		return r<X.r;
	}
}a[N];

int n,T,ans,f[N];
DB L,W;

void init(){
	memset(f, 127, sizeof(f));
	ans=f[n];
}

DB p2(DB x){return x*x;} 

int main(){
	io>>T;
	while(T--){
		io>>n>>L>>W;
		init();
		for(int i=0; i<n; i++){
			DB x,r; 
			io>>x>>r;
			if(r<=W/2.0) a[i]={x,x};
			else{
				DB d=sqrt(p2(r)-p2(W/2.0));
				a[i]={x-d, x+d};
			}
		}
		sort(a, a+n);
		for(int i=0; i<n; i++){
			if(a[i].l<=0) f[i]=1;
			for(int j=0; j<i; j++) if(a[j].r>=a[i].l) f[i]=min(f[i], f[j]+1);
			if(a[i].r>=L) ans=min(ans, f[i]);
		}
		if(ans<f[n]) printf("%d\n", ans);
		else puts("-1");
	}
	return 0;
} 
