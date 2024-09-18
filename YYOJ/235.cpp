#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=5e5+5;

char ch;
int n,m,q,x;
ll bit[N];

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
	scanf("%d%d",&n,&q);
	while(q--){
		scanf("%*[^A-C]%c",&ch);
		if(ch=='A'){
			scanf("%d",&m);
			printf("%lld\n",getsum(m));
		}else if(ch=='B'){
			scanf("%d%d",&m,&x);
			update(m,x);
		}else{
			scanf("%d%d",&m,&x);
			update(m,-x);
		}
	}
	return 0;
} 
