#include<bits/stdc++.h>
using namespace std;

const int N=14;

int n,m,ans,u,v,w,g[N][N],f[N][1<<N],STA,p[N][1<<N],INF;
int lg2[1<<N];

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

void init(){
    for(int i=0; i<=n; i++) lg2[1<<i]=i;
}

int lowbit(int x){return x&-x;}

int main(){
	memset(f, 127, sizeof(f));
    memset(p, 127, sizeof(p));
	memset(g, 127, sizeof(g));
	ans=INF=f[0][0];
	read(n); read(m); STA=1<<n;
    init();
	for(int i=1; i<=m; i++){
		read(u); read(v); read(w);
		u--; v--;
		g[u][v]=min(g[u][v], w);
		g[v][u]=min(g[v][u], w);
	}
    for(int i=1; i<STA; i++){
        int j=i&(i-1), v=lg2[lowbit(i)];
        for(int u=0; u<n; u++) p[u][i]=min(p[u][j], g[u][v]);
    }
    for(int u=0; u<n; u++) f[0][1<<u]=0;
    for(int dep=1; dep<=n; dep++){
        for(int i=1; i<STA; i++){
            for(int j=i&(i-1); j; j=i&(j-1)){
                int k=i^j; int l=k;
                int sum=0;
                while(l && sum<INF){
                    int u=lg2[lowbit(l)];
                    sum+=p[u][j];
                    if(p[u][j]>=INF) sum=INF;
                    l-=lowbit(l);
                }
                if(sum<INF && f[dep-1][j]<INF) f[dep][i]=min(f[dep][i], f[dep-1][j]+dep*sum);
            }
        }
    }
    for(int dep=0; dep<=n; dep++) ans=min(ans, f[dep][STA-1]);
	printf("%d", ans);
	return 0;
}
