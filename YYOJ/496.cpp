#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=3e2+5;
const int Co=1e2+5;
const int Q=1e5+5;

int a[N][N],n,m,x,y,X,Y,c,q,k;
ll bit[N][N][Co],out[Q],t;

ll lowbit(ll x)
{
	return x&-x;
}

void norm_update(int x,int y,int now)
{
	for(int i=x;i<=n;i+=lowbit(i))
	for(int j=y;j<=m;j+=lowbit(j)){
		bit[i][j][a[x][y]]--;
		bit[i][j][now]++;
	}
	a[x][y]=now;
}

ll getsum(int x,int y,int c)
{
	ll sum=0;
	for(int i=x;i>0;i-=lowbit(i))
	for(int j=y;j>0;j-=lowbit(j))
		sum+=bit[i][j][c];
	return sum;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		scanf("%d",&x);
		norm_update(i,j,x);
	}
	scanf("%d",&q);
	while(q--){
		scanf("%d",&k);
		if(k==1){
			scanf("%d%d%d",&x,&y,&c);
			norm_update(x,y,c);
		}else{
			scanf("%d%d%d%d%d",&x,&X,&y,&Y,&c);
			out[++t]=getsum(X,Y,c)-getsum(X,y-1,c)-getsum(x-1,Y,c)+getsum(x-1,y-1,c);
		}
	}
	for(int i=1;i<t;i++)
		printf("%lld\n",out[i]);
	printf("%lld",out[t]);
	return 0;
} 
