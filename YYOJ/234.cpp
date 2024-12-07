#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=5e4+5;

int n,m,k,l,r;
ll bit[N],Bit[N];

ll lowbit(ll x)
{
	return x&-x;
}

void update(ll* bit,int k,ll ad)
{
	for(;k<=N;k+=lowbit(k))
		bit[k]+=ad;
}

ll getsum(ll* bit,int k)
{
	ll sum=0;
	for(;k>0;k-=lowbit(k))
		sum+=bit[k];
	return sum;
} 

int main()
{
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d",&k);
		if(k==1){
			scanf("%d%d",&l,&r);
			update(bit,l,1);
			update(Bit,r+1,1);
		}else{
			scanf("%d%d",&l,&r);
			printf("%lld\n",getsum(bit,r)-getsum(Bit,l));
		}
	}
	return 0;
}
