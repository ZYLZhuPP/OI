#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;
const int STA=1<<5;

int n,Q,ans,u,v,w;
int head[N],to[2*N],nxt[2*N],val[2*N],t;
int f[N][STA];

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(; !isdigit(ch); ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc())
		x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1;
}

void add(int u, int v, int w){
	nxt[++t]=head[u];
	to[t]=v;
	val[t]=w;
	head[u]=t;
}

void dfs(int u, int pre){
    int v;
    for(int i=head[u]; i,v=to[i]; i=nxt[i])if(v^pre){
        dfs(v, u);
        for(int sta=0; sta<STA; sta++){
            for(int sta1=0; sta1<STA; sta1++)if(!(sta&sta1))
                f[u][sta|sta1]=min(f[u][sta|sta1], f[u][sta]+f[v][sta1]+val[i]);
        }
    }
}

int main(){
    read(Q);
	while(Q--){
        t=0;
        memset(head, 0, sizeof(head));
        memset(f, 63, sizeof(f));
        ans=f[0][0];
        read(n);
        for(int i=1; i<=n; i++){
            read(w); w--;
            if(~w) f[i][1<<w]=0;
            f[i][0]=0;
        }
        for(int i=1; i<n; i++){
            read(u); read(v); read(w);
            add(u,v,w); add(v,u,w);
        }
        dfs(1, -1);
        for(int i=1; i<=n; i++) ans=min(ans, f[i][STA-1]);
        printf("%d\n", ans);
	} 
	return 0;
}
