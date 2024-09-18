#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=205;

int n,m,u,v;
ll siz[N],f[N][N],val[N];
int head[N],to[N<<1],nxt[N<<1],t;

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(; !isdigit(ch); ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc())
		x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1;
}

void add(int u, int v){
	nxt[++t]=head[u];
	to[t]=v;
	head[u]=t;
}

void dfs(int u, int pre){
	siz[u]=1;
	f[u][1]=val[u];
	int v;
	for(int i=head[u]; i,v=to[i]; i=nxt[i])if(v^pre){
		dfs(v, u);
		siz[u]+=siz[v];
		for(int j=m+1; j>=2; j--){
			for(int k=1; k<=siz[v]; k++)if(k<j) f[u][j]=max(f[u][j], f[u][j-k]+f[v][k]);
		}
	}
}

int main(){
	while(read(n) && read(m) && n){
		memset(f, 0, sizeof(f));
		memset(head, 0, sizeof(head));
		t=0;
		for(int u=1; u<=n; u++){
			read(v); read(val[u]);
			add(u, v); add(v, u);
		}
		dfs(0, -1);
		printf("%lld\n", f[0][m+1]);
	}
	return 0;
}
