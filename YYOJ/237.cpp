#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=5e3+5;

int n,m,x,y,X,Y,k;
ll bit[N][N],ad;

#define lowbit(x) (x&-x)

void norm_update(int x,int y,ll ad)
{
	for(int i=x;i<=n;i+=lowbit(i))
	for(int j=y;j<=m;j+=lowbit(j))
		bit[i][j]+=ad;
}

ll getsum(int x,int y)
{
	ll sum=0;
	for(int i=x;i>0;i-=lowbit(i))
	for(int j=y;j>0;j-=lowbit(j))
		sum+=bit[i][j];
	return sum;
}

int main()
{
	scanf("%d%d",&n,&m);
	while(~scanf("%d",&k)){
		if(k==1){
			scanf("%d%d%lld",&x,&y,&ad);
			norm_update(x,y,ad);
		}else if(k==2){
			scanf("%d%d%d%d",&x,&y,&X,&Y);
			printf("%lld\n",getsum(X,Y)-getsum(X,y-1)-getsum(x-1,Y)+getsum(x-1,y-1));
		}
	}
	return 0;
}
