#include<bits/stdc++.h>
using namespace std;

const int N=5e4+5;

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
    int u,v,val,co;
    bool operator < (Edge X) const{
        if(val^X.val) return val<X.val;
        return co<X.co;
    }
};
vector<Edge > g;

int n,m,need,ans,fa[N];

int find(int x){
    if(x^fa[x]) fa[x]=find(fa[x]);
    return fa[x];
}

void merge(int u, int v){
    fa[u]=v;
}

void init(){
    for(int i=0; i<n; i++) fa[i]=i;
}

bool ok(int d){
    init();
    int white=0, s=0;
    vector<Edge > g_(g);
    for(auto &e: g_) if(!e.co) e.val+=d;
    sort(g_.begin(), g_.end());
    for(auto e: g_){
        int u=e.u, v=e.v, w=e.val, co=e.co;
        int fu=find(u), fv=find(v);
        if(fu^fv){
            s+=w; white+=!co;
            merge(fu, fv);
        }
    }
    if(white>=need) ans=s-d*need;
    return white>=need;
}

int main(){
    io>>n>>m>>need;
    for(int i=1; i<=m; i++){
        int u, v, w, co;
        io>>u>>v>>w>>co;
        g.push_back({u,v,w,co});
    }
    int l=-100, r=100;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ok(mid)) l=mid+1;
        else r=mid-1;
    }
    printf("%d", ans);
    return 0;
}
