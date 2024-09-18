#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5;

int n,p,k,ans=-1,l,r,m,i;
int tot,dis[N],head[N],q[N];

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

struct edge{
	int x,y,k;
}a[N];

struct Edge{
	int to,nxt,w;
}e[N];

void add(int u, int v, int w){
	e[++tot].to=v;
	e[tot].w=w;
	e[tot].nxt=head[u];
	head[u]=tot;
}

bool ok(int x){
	tot=0;memset(head,0,sizeof(head));
	for(int i=1; i<=p; i++)
		if(a[i].k>x) add(a[i].x,a[i].y,1), add(a[i].y,a[i].x,1);
		else add(a[i].x,a[i].y,0), add(a[i].y,a[i].x,0);
	for(int i=2; i<=n; i++) dis[i]=INT_MAX/3;
	dis[1]=0;
	int h=5000,t=5001,u,v;
	q[5001]=1;
	while(h!=t){
		u=q[++h];
		for(int i=head[u]; i,v=e[i].to; i=e[i].nxt)
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				if(e[i].w) q[++t]=v;
				else if(q[h]) q[--h]=v, h--;
				else q[h--]=v;
			}
	}
	return dis[n]<=k;
}

int main(){
	read(n); read(p); read(k);
	for(i=1; i<=p; i++) read(a[i].x), read(a[i].y), read(a[i].k), r=max(r,a[i].k);
	while(l<=r){
		m=l+r>>1;
		if(ok(m)) r=m-1, ans=m;
		else l=m+1;
	}
	printf("%d",ans);
	return 0;
}
