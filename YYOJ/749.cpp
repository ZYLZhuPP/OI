#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e3+5;
const ll Mo=2147483647;

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
    ll to,val;
};
vector<Edge > g[N];

ll n,m,ans,dis[N],id[N];

void spfa(ll rt){
    bool inq[N];
    memset(inq, 0, sizeof(inq));
    memset(dis, 31, sizeof(dis));
    dis[rt]=0;
    queue<ll > q; q.push(rt); inq[rt]=1;
    while(!q.empty()){
        ll u=q.front(); q.pop(); inq[u]=0;
        for(auto e: g[u]){
            ll v=e.to, w=e.val;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!inq[v]) q.push(v), inq[v]=1;
            }
        }
    }
}

void add(ll u, ll v, ll w){
    g[u].push_back({v,w});
}

bool cmp(ll X, ll Y){
    return dis[X]<dis[Y];
}

int main(){
    io>>n>>m;
    for(int i=1; i<=m; i++){
        ll u,v,w;
        io>>u>>v>>w;
        add(u, v, w);
        add(v, u, w);
    }
    spfa(1);
    for(int i=1; i<=n; i++) id[i]=i;
    sort(id+1, id+n+1, cmp);
    ans=1;
    for(int i=2; i<=n; i++){
        ll u=id[i], cnt=0;
        for(auto e: g[u]) if(dis[u]==dis[e.to]+e.val) cnt++;
        (ans*=cnt)%=Mo;
    }
    printf("%lld", ans);
    return 0;
}
