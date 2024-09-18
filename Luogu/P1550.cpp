#include<bits/stdc++.h>
using namespace std;

const int N=305;
const int M=N*N+5;

struct Edge{
    int u,v,w;
    bool operator <(const Edge X){
        return w<X.w;
    }
}e[M];

int n,w,ans,esiz,fa[N];

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

void add(int u, int v, int w){
    e[++esiz]={u, v, w};
}

int find(int x){
    if(fa[x]^x) return fa[x]=find(fa[x]);
    return x;
}

void merge(int u, int v){
    fa[u]=v;
}

void init(){
    for(int i=0; i<=n; i++) fa[i]=i;
}

int main(){
    read(n);
    init();
    for(int i=1; i<=n; i++){
        read(w);
        add(0, i, w);
    }
    for(int u=1; u<=n; u++)
        for(int v=1; v<=n; v++){
            read(w);
            if(u<v){
                add(u, v, w);
            }
        }
    sort(e+1, e+esiz+1);
    for(int i=1; i<=esiz; i++){
        int u=e[i].u, v=e[i].v;
        int fu=find(u), fv=find(v);
        if(fu^fv){
            merge(fu, fv);
            ans+=e[i].w;
        }
    }
    printf("%d", ans);
    return 0;
}
