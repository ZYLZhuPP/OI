#include<bits/stdc++.h>
using namespace std;

const int N=155;
const double INF=1e20;

int x[N],y[N],n,co[N],color;
double dis[N][N],len[N],ma[N],ans=INF;
char st[N];

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

int p2(int x){return x*x;}

double dist(int u, int v){
    return sqrt(p2(x[u]-x[v])+p2(y[u]-y[v]));
}

int main(){
    read(n);
    for(int i=1; i<=n; i++){
        read(x[i]); read(y[i]);
    }
    for(int i=1; i<=n; i++){
        scanf("%s", st+1);
        for(int j=1; j<=n; j++)
            if(st[j]^'0') dis[i][j]=dist(i,j);
            else dis[i][j]=INF;
    }
    for(int k=1; k<=n; k++)
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++) if(dis[i][j]>dis[i][k]+dis[k][j])
                dis[i][j]=dis[i][k]+dis[k][j];
    for(int i=1; i<=n; i++){
        if(!co[i]){
            co[i]=++color;
            for(int j=1; j<=n; j++) if(dis[i][j]<INF){
                co[j]=color;
                ma[i]=max(ma[i], dis[i][j]);
            }
        }else{
            for(int j=1; j<=n; j++) if(i^j && co[i]==co[j]){
                len[co[i]]=max(len[co[i]], dis[i][j]);
                ma[i]=max(ma[i], dis[i][j]);
            }
        }
    }
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++) if(co[i]^co[j]){
            ans=min(ans, max(len[co[i]], max(len[co[j]], dist(i, j)+ma[i]+ma[j])));
        }
    printf("%.6lf", ans);
    return 0;
}
