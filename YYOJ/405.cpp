#include<bits/stdc++.h>
using namespace std;

const int N=505;

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

struct W{
	int t,w;
	bool operator < (const W X) const{
		return w>X.w;
	}
}a[N];

int n,m;
bool b[N];

int main(){
	io>>m;
	io>>n;
	for(int i=0; i<n; i++) io>>a[i].t;
	for(int i=0; i<n; i++) io>>a[i].w;
	sort(a, a+n);
	for(int i=0; i<n; i++){
		int p=a[i].t;
		while(p && b[p]) p--;
		if(!p) m-=a[i].w;
		else b[p]=1;
	}
	printf("%d", m);
	return 0;
}
