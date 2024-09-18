#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5, INF=0x1f1f1f1f;

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

int n,m,s,ans,a[N][N],dis[N];

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
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!inq[v]) q.push(v), inq[v]=1;
            }
        }
    }
}

bool ok(int k){
    for(int u=1; u<=n; u++)
        for(auto &e: g[u]) e.val=(a[u][e.to]>k);
    spfa(1);
    return dis[n]<=s;
}

void add(int u, int v, int w){
    g[u].push_back({v,w});
}

int main(){
    io>>n>>m>>s;
    int l=0, r=0;
    for(int i=1; i<=m; i++){
        int u,v,w;
        io>>u>>v>>w;
        a[u][v]=a[v][u]=w;
        r=max(r, w);
        add(u, v, w);
        add(v, u, w);
    }
    spfa(1);
    if(dis[n]==INF){
        puts("-1");
        return 0;
    }
    while(l<=r){
        int mid=(l+r)>>1;
        if(ok(mid)) ans=mid, r=mid-1;
        else l=mid+1;
    }
    printf("%d", ans);
    return 0;
}
