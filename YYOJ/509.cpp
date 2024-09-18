#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

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

int n,m;
vector<int> g[N];
int dep[N],c[N],f[N][25];

int lca(int x, int y){
	if(dep[x]<dep[y])
		swap(x,y);
	for(int i=20; i>=0; i--)
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if(x==y) return x;
	for(int i=20; i>=0; i--)
		if(f[x][i]^f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}

void dfs(int x, int fa){
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(int i=1; (1<<i)<=dep[x]; i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=0; i<g[x].size(); i++){
		int y=g[x][i];
		if(y==fa) continue;
		dfs(y,x);
	}
}

void Dfs(int x, int fa){
	for(int i=0; i<g[x].size(); i++){
		int y=g[x][i];
		if(y==fa) continue;
		Dfs(y,x);
		c[x]+=c[y];
	}
}

int main(){
	io>>n>>m;
	for(int i=1; i<n; i++){
		int x,y;
		io>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1; i<=m; i++){
		int x,y;
		io>>x>>y;
		c[x]++, c[y]++;
		c[lca(x,y)]-=2;
	}
	Dfs(1,0);
	long long ans=0;
	for(int i=2; i<=n; i++)
		if(!c[i]) ans+=m;
		else if(c[i]==1) ans++;
	printf("%lld", ans);
	return 0;
}
