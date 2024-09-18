#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5, Mo=1e5+3;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^'-')) f=-1;
		for(x=0; isdigit(c); c=gc()) x=x*10+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct Edge{
    int to,val;
};
vector<Edge > g[N];

int n,m,f[N],dis[N];

void spfa(int rt){
    bool inq[N];
    memset(inq, 0, sizeof(inq));
    memset(dis, 31, sizeof(dis));
    dis[rt]=0;
    queue<int > q; q.push(rt); inq[rt]=1;
    while(!q.empty()){
        int u=q.front(); q.pop(); inq[u]=0;
        for(auto e: g[u]){
            int v=e.to, w=e.val;
            if(dis[v]==dis[u]+w) (f[v]+=f[u])%=Mo;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w; f[v]=f[u];
                if(!inq[v]) q.push(v), inq[v]=1;
            }
        }
    }
}

void add(int u, int v, int w){
    g[u].push_back({v,w});
}

int main(){
    io>>n>>m;
    for(int i=1; i<=m; i++){
        int u,v;
        io>>u>>v;
        add(u, v, 1);
        add(v, u, 1);
    }
    f[1]=1;
    spfa(1);
    for(int i=1; i<=n; i++) printf("%d ", f[i]);
    return 0;
}
