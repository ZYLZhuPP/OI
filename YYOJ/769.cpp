#include<bits/stdc++.h>
using namespace std;

typedef double DB;

const int N=3e3+5, M=1e4+5;

struct Edge{
	DB v;
	int to,next;
}a[M];

int n,m,g,head[N];
bool vis[N],f;
DB mid,dis[N];

void add(int x,int y){
	cin>>a[++g].v;
	a[g].to=y;
	a[g].next=head[x];
	head[x]=g;
}

void spfa(int i){
	vis[i]=1;
	for(int j=head[i]; j; j=a[j].next){
		if(dis[a[j].to]>dis[i]+a[j].v-mid){
			dis[a[j].to]=dis[i]+a[j].v-mid;
			if(vis[a[j].to]) return void(f=1);
			else spfa(a[j].to);
		}
	}
	vis[i]=0;
}

bool ok(){
	int i;
	for(i=1; i<=n; i++) dis[i]=vis[i]=f=0;
	for(i=1; i<=n; i++) if(!vis[i] && !f) spfa(i);
	return f;
}

int main(){
	cin>>n>>m;
	for(int i=1; i<=m; i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
	}
	DB l=-1e7,r=1e7;
	while(l<=r){
		mid=(l+r)/2;
		if(ok())r=mid-1e-9;
		else l=mid+1e-9;
	}
	printf("%.8lf\n", l);
	return 0;
}
