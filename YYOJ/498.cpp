#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;

struct smt{//Segment Tree
	long long ma,ad;
}smt[4*N];

#define ma(x) smt[x].ma
#define ad(x) smt[x].ad

char ch[3];
long long a[N],n,m,p,x,Ma;

void pushup(int now)
{
	ma(now)=max(ma(now<<1),ma(now<<1|1));
}

void pushdown(int now,int l,int r)
{
	int mid=l+r>>1;
	ma(now<<1)+=ad(now);ad(now<<1)+=ad(now);
	ma(now<<1|1)+=ad(now);ad(now<<1|1)+=ad(now);
	ad(now)=0;
} 

void update(int now,int l,int r,int goal,int ad)
{
    if(goal<l||goal>r)return;
    if(l==r){a[goal]+=ad;ma(now)=a[goal];return;}
    int mid=l+r>>1;
    update(now<<1,l,mid,goal,ad);
    update(now<<1|1,mid+1,r,goal,ad);
    pushup(now);
}

void find(int now,int l,int r,int x,int y)
{
	if(l>y||r<x)return;
	if(l>=x&&r<=y){Ma=max(Ma,ma(now));return;}
	pushdown(now,l,r);
	int mid=l+r>>1;
	find(now<<1,l,mid,x,y);
	find(now<<1|1,mid+1,r,x,y);
}

void ask(int l,int r)
{
	Ma=0;
	find(1,1,m,l,r);
}

int main()
{
	scanf("%lld%lld",&m,&p);
	for(int i=1;i<=m;i++){
		scanf("%s%lld",ch,&x);
		if(ch[0]=='Q'){
			ask(n-x+1,n);
			printf("%lld\n",Ma);
		}else{
			n++;
			x=(Ma+x)%p;
			update(1,1,m,n,x);
		}
	}
}
