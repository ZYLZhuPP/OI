#include<bits/stdc++.h>
using namespace std;

const int N=105;

int n,m,u,v,w,f[N][N],siz[N],root=1;
int head[N],nxt[N],to[N],t,val[N];

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

void init_dfs(int u){
    siz[u]=1;
    f[u][1]=val[u];
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        init_dfs(v);
        siz[u]+=siz[v];
    }
}

void init(){
    init_dfs(root);
}

void dfs(int u){
    if(siz[u]<=1)
        return;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        for(int j=siz[u];j>=2;j--){
            for(int k=1;k<=siz[v];k++)if(k<j)
                f[u][j]=max(f[u][j],f[u][j-k]+f[v][k]);
        }
    }
}

int main(){
    read(n);read(m);
    for(int i=2;i<=n+1;i++){
        read(u);read(val[i]);
        u++;
        add(u,i);
    }
    init();
    dfs(root);
    printf("%d",f[root][m+1]);
    return 0;
} 
