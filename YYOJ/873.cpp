#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

string st;
int u,v,n,pt,root,ans,res,whisum;
int nxt[N<<1],to[N<<1],head[N],edgesiz;
int whi[N],co[N],f[2][N];
bool del[N];

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

void add(int u, int v){
    nxt[++edgesiz]=head[u];
    to[edgesiz]=v;
    head[u]=edgesiz;
}

void del_edge(int u, int pre){
    whi[u]=co[u];
    int v,ma;
    for(int i=head[u]; i, v=to[i]; i=nxt[i])if(v^pre){
        del_edge(v, u);
        whi[u]+=whi[v];
        ma=max(ma,whi[v]);
    }
    if(!whi[u] || ma==whisum) del[u]=1;
    else pt++, root=u;
}

void dfs1(int u, int pre){
    int v;
    for(int i=head[u]; i, v=to[i]; i=nxt[i])if(v^pre && !del[v]){
        dfs1(v, u);
        co[u]=!co[u];
        co[v]=!co[v];
    }
}

void dfs2(int u, int pre){
    int v;
    for(int i=head[u]; i, v=to[i]; i=nxt[i])if(v^pre && !del[v]){
        dfs2(v, u);
        int ret=f[0][v]+co[v];
        if(ret>=f[0][u]) f[1][u]=f[0][u], f[0][u]=ret;
        else if(ret>f[1][u]) f[1][u]=ret;
    }
    res=max(res, f[0][u]+f[1][u]+co[u]);
}

int main(){
    read(n);
    for(int i=1; i<n; i++){
        read(u); read(v);
        add(u,v); add(v,u);
    }
    cin>>st; st=" "+st;
    for(int i=1; i<=n; i++) co[i]=(st[i]=='W'), whisum+=co[i];
    del_edge(1, -1);
    dfs1(root, -1);
    ans+=(pt-1)*2;
    for(int i=1; i<=n; i++)if(!del[i]) ans+=co[i];
    dfs2(root, -1);
    ans-=res*2;
    printf("%d", ans);
    return 0;
}
