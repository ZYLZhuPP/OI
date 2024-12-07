#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=4e4+5;

int n,x,y;
ll bit[N],pd[N];

ll lowbit(ll x)
{
	return x&-x;
}

void update(int k,ll ad)
{
	for(;k<=N;k+=lowbit(k))
		bit[k]+=ad;
}

ll getsum(int k)
{
	ll sum=0;
	for(;k>0;k-=lowbit(k))
		sum+=bit[k];
	return sum;
} 

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		pd[getsum(x+1)]++;
		update(x+1,1);
	}
	for(int i=0;i<n;i++)
		printf("%lld\n",pd[i]);
	return 0;
} 
