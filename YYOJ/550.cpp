#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1505;
const ll INF=LLONG_MAX/3;

int n,u,v,k;
ll f[3][N],val[N],w;
int head[N],nxt[2*N],to[2*N],t;

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

void dfs(int u,int pre){
    ll d=INF;
    f[2][u]=val[u];
    int v;
    for(int i=head[u];v=to[i],i;i=nxt[i])if(v^pre){
        dfs(v,u);
        d=min(d,f[2][v]-min(f[1][v],f[2][v]));
        f[0][u]+=min(f[1][v],f[2][v]);
        f[1][u]+=min(f[1][v],f[2][v]);
        f[2][u]+=min(f[0][v],min(f[1][v],f[2][v]));
    }
    f[1][u]+=d;
}

int main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(u);read(w);read(k);
        val[u]=w;
        while(k--){
            read(v);
            add(u,v);
            add(v,u);
        }
    }
    dfs(1,-1);
    printf("%lld",min(f[2][1],f[1][1]));
    return 0;
}
