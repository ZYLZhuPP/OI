#include<bits/stdc++.h>
using namespace std;

const int N=205;

int n,m,x,u,v,g[N][N],pu[N],pv[N],ans;
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

bool wide(int u){
    for(int v=1; v<=m; v++)if(!vis[v] && g[u][v]){
        vis[v]=1;
        if(!pv[v] || wide(pv[v])){
            pu[u]=v; pv[v]=u;
            return 1;
        }
    }
    return 0;
}

int main(){
    read(n); read(m);
    for(int u=1; u<=n; u++){
        read(x);
        while(x--){
            read(v);
            g[u][v]=1;
        }
    }
    for(int u=1; u<=n; u++){
        memset(vis, 0, sizeof(vis));
        ans+=wide(u);
    }
    printf("%d", ans);
    return 0;
}
