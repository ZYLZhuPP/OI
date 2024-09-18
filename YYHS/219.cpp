#include<bits/stdc++.h>
using namespace std;

const int N=55;
const int X=1e9+5;

int n,x[N],y[N],ans;
bool vis[N];

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
    bool f(0);
	char ch(gc());
	for(; !isdigit(ch); f|=!(ch^45), ch=gc()) if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc()) x=(x<<3)+(x<<1)+(ch^48);
	if(f) x=-x;
	return 1; 
}

int dfs(int u, int k){
    vis[u]=1;
    int res=1;
    for(int v=1; v<=n; v++) if(!vis[v]){
        if(abs(x[u]-x[v])+abs(y[u]-y[v])<=2*k) res+=dfs(v, k);
    }
    return res;
}

bool ok(int k){
    memset(vis, 0, sizeof(vis));
    return dfs(1, k)==n;
}

int main(){
    read(n);
    for(int i=1; i<=n; i++) read(x[i]), read(y[i]);
    int l=0, r=2*X;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ok(mid)) ans=mid, r=mid-1;
        else l=mid+1;
    }
    printf("%d", ans);
    return 0;
}
