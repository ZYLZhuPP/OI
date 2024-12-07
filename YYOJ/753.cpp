#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=510,M=1e4+6;

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

struct edge{
    int a,b;
    int w;
    bool operator<(const edge &a) const{
        return w<a.w;
    }
}ed[M];

int e[N*2],w[N*2],ne[N*2],h[N],idx,n,m;
int dist[N][N];
int p[N];
ll sum=0,res=1e18;

int find(int x){
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}

void add(int a,int b,int c){
    e[idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx++;
}

void dfs(int u,int fa,int v,int d[]){
    d[u]=v;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j=e[i];
        if(j!=fa){
            dfs(j,u,max(v,w[i]),d);
        }
    }
}

int main()
{
    io>>n>>m;
    memset(h,-1,sizeof(h));
    for(int i=1;i<=n;i++) p[i]=i;
    for(int i=0;i<m;i++) io>>ed[i].a>>ed[i].b>>ed[i].w;
    sort(ed,ed+m);
    for(int i=0;i<m;i++){
        int a=find(ed[i].a),b=find(ed[i].b),w=ed[i].w;
        if(a!=b){
            p[a]=b;
            sum+=w;
            add(a,b,w);
            add(b,a,w);
        }
    }
    for(int i=1;i<=n;i++) dfs(i,-1,0,dist[i]);
    for(int i=0;i<m;i++){
        int a=ed[i].a,b=ed[i].b,w=ed[i].w;
        if(w>dist[a][b]){
            res=min(sum+w-dist[a][b],res);
        }
    }
    printf("%lld",res);
    return 0;
}
