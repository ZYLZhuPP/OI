#include<bits/stdc++.h>
using namespace std;

const int N=105;

int n,m,u,v,w,f[N][N],siz[N],son[N][3],root=1;
int head[N],nxt[2*N],to[2*N],t,val[2*N];

#define gc() getchar()

template<class T>
inline void read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(;!isdigit(ch);ch=gc())
		if(!(ch^'-'))
			f=-1;
	for(;isdigit(ch);ch=gc())
		x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
}

void add(int u,int v,int w){
	nxt[++t]=head[u];
	to[t]=v;
	val[t]=w;
	head[u]=t;
}

void dfs_init(int u,int pre){
	siz[u]=1;
	for(int i=head[u];i;i=nxt[i])if(to[i]^pre){
		int v=to[i];
		son[u][++son[u][0]]=v;
		f[v][1]=val[i];
		dfs_init(v,u);
		siz[u]+=siz[v];
	}
}

void init(){
	dfs_init(root,-1);
}

void dfs(int u){
	if(siz[u]<=1)
		return;
	int lc=son[u][1],rc=son[u][2];
	dfs(lc);
	dfs(rc);
	for(int i=0;i<=siz[lc];i++)
	for(int j=0;j<=siz[rc];j++)
		f[u][i+j+1]=max(f[u][i+j+1],f[lc][i]+f[rc][j]+f[u][1]);
}

int main(){
	read(n);read(m);
	for(int i=1;i<n;i++){
		read(u);read(v);read(w);
		add(u,v,w);
		add(v,u,w);
	}
	init();
	dfs(root);
	printf("%d",f[root][m+1]);
	return 0;
} 
