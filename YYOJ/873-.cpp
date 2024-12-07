#include<bits/stdc++.h>
using namespace std;

const int N=1e5;

int n,u,v,ans,co[N+5],whi[N+5],root,sum;
int head1[N+5],to1[2*N+5],nxt1[2*N+5],edgesiz1;
int head2[N+5],to2[2*N+5],nxt2[2*N+5],edgesiz2;
char ch;

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(; !isdigit(ch); ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc()) x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1;
}

void add1(int u, int v){
	nxt1[++edgesiz1]=head1[u];
	to1[edgesiz1]=v;
	head1[u]=edgesiz1;
}

void add2(int u, int v){
	nxt2[++edgesiz2]=head2[u];
	to2[edgesiz2]=v;
	head2[u]=edgesiz2;
}

void dfs1(int u, int pre){
	whi[u]=co[u];
	int v;
	for(int i=head1[u]; i,v=to1[i]; i=nxt1[i])if(v^pre){
		dfs1(v,u);
		if(whi[v] && (whi[v]^sum)) add2(u,v), root=u;
		whi[u]+=whi[v];
	}
}

int dfs2(int u, int pre){
	int v,cnt=0,res=0;
	for(int i=head2[u]; i,v=to2[i]; i=nxt2[i])if(v^pre){
		cnt++;
		int ret=dfs2(v,u);
		res+=ret;
	}
	return res+cnt+1+(cnt+co[u]+1)%2;
}

int main(){
	read(n);
	for(int i=1; i<n; i++){
		read(u); read(v);
		add1(u,v);
		add1(v,u);
	}
	for(int i=1; i<=n; i++){
		cin>>ch;
		co[i]=(ch=='W');
		sum+=co[i];
	}
	dfs1(1, -1);
	ans=dfs2(root, -1);
	printf("%d", ans);
	return 0;
}
