#include<bits/stdc++.h>
using namespace std;

const int N=5e4+5;

int n,k,fal,fa[N],ki[N];

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
    bool f(0);
	char ch(gc());
	for(; !isdigit(ch); f|=!(ch^45), ch=gc()) if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc()) x=(x<<3)+(x<<1)+(ch^48);
	if(f) x=-x;
	return 1; 
}

int find(int u){
	if(fa[u]^u){
		int f=fa[u];
		fa[u]=find(f);
		(ki[u]+=ki[f])%=3;
	}
	return fa[u];
} 

void merge(int u, int v, int w){
	fa[u]=v;
	(ki[u]+=w)%=3;
} 

void init(){
	for(int i=1; i<=n; i++) fa[i]=i;
}

int main(){
	read(n); read(k);
	init();
	int u,v,p;
	while(k--){
		read(p); read(u); read(v);
		if(u>n || v>n){
			fal++;
			continue;
		}
		int fu=find(u), fv=find(v);
		if(p==1){
			if(fu^fv) merge(fu, fv, 3-ki[u]+ki[v]);
			else if(ki[u]^ki[v]) fal++;
		}else{
			if(fu^fv) merge(fu, fv, 4+ki[v]-ki[u]);
			else if(((ki[u]-ki[v]+3)%3)^1) fal++;
		}
	}
	printf("%d", fal);
	return 0;
}

