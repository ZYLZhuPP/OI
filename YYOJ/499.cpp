#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e5+5;

struct smt{//Segment Tree
	ll sum,ma;
}smt[4*N];

#define sum(x) smt[x].sum
#define ma(x) smt[x].ma

ll a[N],n,m,x,l,r,Sum;

#define gc() getchar()

template<typename T>
inline void read(T *x)
{
	(*x)=0;
	int f=1;
	char ch=gc();
	for(;!isdigit(ch);ch=gc())
		if(!(ch^'-'))
			f=-1;
	for(;isdigit(ch);ch=gc())
		(*x)=((*x)<<3)+((*x)<<1)+(ch^48);
	(*x)*=f;
}

void pushup(int now)
{
	ma(now)=max(ma(now<<1),ma(now<<1|1));
    sum(now)=sum(now<<1)+sum(now<<1|1);
}

void build(int now,int l,int r)
{
    if(l==r){ma(now)=sum(now)=a[l];return;}
    int mid=l+r>>1;
    build(now<<1,l,mid);
    build(now<<1|+1,mid+1,r);
    pushup(now);
}

void inr_update(int now,int l,int r,int x,int y)
{
	if(l>y||r<x||ma(now)<=1)return;
	if(l==r){a[l]=sqrt(a[l]);ma(now)=sum(now)=a[l];return;}
	int mid=l+r>>1;
	inr_update(now<<1,l,mid,x,y);
	inr_update(now<<1|1,mid+1,r,x,y);
	pushup(now);
}

void find(int now,int l,int r,int x,int y)
{
	if(l>y||r<x)return;
	if(l>=x&&r<=y){Sum+=sum(now);return;}
	int mid=l+r>>1;
	find(now<<1,l,mid,x,y);
	find(now<<1|1,mid+1,r,x,y);
}

void ask(int l,int r)
{
	Sum=0;
	find(1,1,n,l,r);
}

int main()
{
    read(&n);
    for(int i=1;i<=n;i++)
    	read(&a[i]);
    build(1,1,n);
    read(&m);
    while(m--){
    	read(&x);read(&l);read(&r);
    	if(x==1){
    		ask(l,r);
    		printf("%lld\n",Sum);
		}else
			inr_update(1,1,n,l,r);
	}
}
