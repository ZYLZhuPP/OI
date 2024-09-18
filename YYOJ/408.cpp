#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

int n,x,l,r,ad,q,k;
ll bit[N],a[N],out[N],t;

int lowbit(int x)
{
	return x&-x;
}

void update(int k,int ad)
{
	for(;k<=n;k+=lowbit(k))
		bit[k]+=ad;
}

void q_update(int l,int r,int ad)
{
	update(l,ad);
	update(r+1,-ad);
}

ll getnum(int k)
{
	ll num=0;
	for(;k>0;k-=lowbit(k))
		num+=bit[k];
	return num;
} 

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		update(i,a[i]-a[i-1]);
	}
	while(q--){
		scanf("%d",&k);
		if(k==1){
			scanf("%d%d%d",&l,&r,&ad);
			q_update(l,r,ad);
		}
		else{
			scanf("%d",&x);
			out[++t]=getnum(x);
		}
	}
	for(int i=1;i<t;i++)
		printf("%lld\n",out[i]);
	printf("%lld",out[t]);
	return 0;
} 
