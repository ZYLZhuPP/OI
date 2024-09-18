#include<bits/stdc++.h>
using namespace std;

typedef double DB;

const int N=2505;
const DB dd=5e-5, INF=1e20;

int k,n,s[N],p[N],u,siz[N];
bool g[N][N];
DB f[N][N],ans;

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

void dfs(int u){
	siz[u]=1;
	for(int v=1; v<=n; v++) if(g[u][v]){
		dfs(v); siz[u]+=siz[v];
		for(int i=siz[u]; i>1; i--){
			for(int j=min(i-1, siz[v]); j>=1; j--)
				f[u][i]=max(f[u][i], f[u][i-j]+f[v][j]);
		}
	}
}

void init(){
	for(int i=0; i<=n; i++){
		for(int j=1; j<=n+1; j++) f[i][j]=-INF;
	}
}

bool ok(DB o){
	init();
	for(int i=0; i<=n; i++) f[i][1]=(DB)p[i]-o*s[i];
	dfs(0);
	return f[0][k+1]>=0;
}

int main(){
	read(k); read(n);
	DB r=0;
	for(int i=1; i<=n; i++){
		read(s[i]); read(p[i]); read(u);
		r=max(r, (DB)p[i]/s[i]);
		g[u][i]=1;
	}
	DB l=0;
	while(l<=r){
		DB mid=(l+r)/2.0;
		if(ok(mid)) ans=mid, l=mid+dd;
		else r=mid-dd;
	}
	printf("%.3lf", ans);
	return 0;
} 
