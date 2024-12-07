#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

int n,x,l,r,q,k;
ll bit[N],Bit[N],out[N],t;

ll lowbit(ll x)
{
	return x&-x;
}

void norm_update(int k,ll ad)
{
	for(;k<=n;k+=lowbit(k))
		bit[k]+=ad;
}

void Norm_update(int k,ll ad)
{
	for(;k<=n;k+=lowbit(k))
		Bit[k]+=ad;
}

void q_update(int l,int r,ll ad)
{
	norm_update(l,ad);
	Norm_update(l,ad*l);
	r++;
	norm_update(r,-ad);
	Norm_update(r,-ad*r);
}

void pt_update(int k,ll ad)
{
	q_update(k,k,ad);
}

ll getnum(int k)
{
	ll num=0;
	for(;k>0;k-=lowbit(k))
		num+=bit[k];
	return num;
} 

ll getsum(int k)
{
	ll sum=(k+1)*getnum(k);
	for(k;k>0;k-=lowbit(k))
		sum-=Bit[k];
	return sum;
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		pt_update(i,x);
	}
	while(q--){
		scanf("%d",&k);
		if(k==1){
			scanf("%d%d%d",&l,&r,&x);
			q_update(l,r,x);
		}
		else{
			scanf("%d%d",&l,&r);
			out[++t]=getsum(r)-getsum(l-1);
		}
	}
	for(int i=1;i<t;i++)
		printf("%lld\n",out[i]);
	printf("%lld",out[t]);
	return 0;
} 
