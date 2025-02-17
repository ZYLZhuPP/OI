#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=2e5;

ll n,val[N+5],Q,u,v,ans,t,ne;
int fa[N+5],head[N+5],to[2*N+5],nxt[2*N+5],edgesiz;

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

void init_fa(int u, int pre){
    fa[u]=pre;
    int v;
    for(int i=head[u]; i, v=to[i]; i=nxt[i])if(v^pre) init_fa(v, u);
}

void init(){
    init_fa(1, -1);
}

void sqrt_dfs(int u, int pre){
    val[u]=sqrt(val[u]);
    int v;
    for(int i=head[u]; i, v=to[i]; i=nxt[i])if(v^pre) sqrt_dfs(v, u);
}

void trsqrt(int u){
    sqrt_dfs(u, fa[u]);
}

void sum_dfs(int u, int pre){
    ans+=val[u];
    int v;
    for(int i=head[u]; i, v=to[i]; i=nxt[i])if(v^pre) sum_dfs(v, u);
}

void getsum(int u){
    sum_dfs(u, fa[u]);
}

int main(){
    read(n);
    for(int i=1; i<n; i++){
        read(u); read(v);
        add(u,v); add(v,u);
    }
    init();
    for(int i=1; i<=n; i++) read(val[i]);
    read(Q);
    while(Q--){
        read(t);
        if(t==1){
            read(u);
            trsqrt(u);
        }else if(t==2){
            read(u); read(ne);
            val[u]=ne;
        }else{
            read(u);
            ans=0;
            getsum(u);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
