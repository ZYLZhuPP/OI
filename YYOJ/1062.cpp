#include<bits/stdc++.h>
using namespace std;

const int N=3e4+5;

int u,v,T,fa[N],fo[N],siz[N];
char st[5];

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

void init(){
    for(int i=1; i<N; i++) fa[i]=i, siz[i]=1;
}

int find(int u){
    if(u^fa[u]){
        int f=fa[u];
        fa[u]=find(fa[u]);
        fo[u]+=fo[f];
        return fa[u];
    }
    return u;
}

void merge(int u, int v){
    fo[u]+=siz[v];
    siz[v]+=siz[u];
    fa[u]=fa[v];
}

int main(){
    read(T);
    init();
    while(T--){
        scanf("%s", st);
        read(u); read(v);
        int fu=find(u), fv=find(v);
        if(st[0]=='M'){
            merge(fu, fv);
        }else{
            if(fv^fu) puts("-1");
            else printf("%d\n", abs(fo[u]-fo[v])-1);
        }
    }
    return 0;
}
