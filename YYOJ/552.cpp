#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;

int n,u,v,root=0,ma1[N],ma2[N],up[N],id1[N],id2[N],ans;
int head[N],to[2*N],nxt[2*N],t;

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

void add(int u,int v){
	nxt[++t]=head[u];
	to[t]=v;
	head[u]=t;
}

void dfs1(int u,int pre){
	int v;
	for(int i=head[u];v=to[i],i;i=nxt[i])if(v^pre){
		dfs1(v,u);
		if(ma1[u]<=ma1[v]+1){
			ma2[u]=ma1[u];
			id2[u]=id1[u];
			ma1[u]=ma1[v]+1;
			id1[u]=v;
		}else if(ma2[u]<ma1[v]+1){
			ma2[u]=ma1[v]+1;
			id2[u]=v;
		}
	}
	ans=max(ans,ma1[u]+ma2[u]);
}

void dfs2(int u,int pre){
	if(pre^-1){
		if(id1[pre]^u)
			up[u]=max(up[pre],ma1[pre])+1;
		else
			up[u]=max(up[pre],ma2[pre])+1;
	}
	int v;
	for(int i=head[u];v=to[i],i;i=nxt[i])if(v^pre)
		dfs2(v,u);
}

int main(){
	read(n);
	for(int i=1;i<n;i++){
		read(u);read(v);
		add(u,v);
		add(v,u);
	}
	dfs1(root,-1);
	dfs2(root,-1);
	for(int i=0;i<n;i++)if(max(up[i]+ma1[i],ma1[i]+ma2[i])==ans)
		printf("%d\n",i);
	return 0;
} 
