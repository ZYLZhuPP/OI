#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e5+5;

#define Mo(x) ((x)%mo)

struct SMT{//Segment Tree
	ll sum,ad,ma,mu;
}smt[4*N];

#define sum(x) smt[x].sum
#define ma(x) smt[x].ma
#define ad(x) smt[x].ad
#define mu(x) smt[x].mu

#define nowl now<<1
#define nowr now<<1|1

ll a[N],n,m,x,y,l,r,Sum,Ma,mo;

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
	ma(now)=max(ma(nowl),ma(nowr));
    sum(now)=Mo(sum(nowl)+sum(nowr));
}

void pushdown_(int now,int l,int r,int fa)
{
	ma(now)=Mo(Mo(ma(now)*mu(fa))+ad(fa));
	sum(now)=Mo(Mo(sum(now)*mu(fa))+Mo((r-l+1)*ad(fa)));
	ad(now)=Mo(ad(now)*mu(fa)+ad(fa));
	mu(now)=Mo(mu(now)*mu(fa));
}

void pushdown(int now,int l,int r)
{
	int mid=l+r>>1;
	pushdown_(nowl,l,mid,now);
	pushdown_(nowr,mid+1,r,now);
	mu(now)=1;ad(now)=0;
} 

void build(int now,int l,int r)
{
	mu(now)=1;
    if(l==r){ma(now)=sum(now)=Mo(a[l]);return;}
    int mid=l+r>>1;
    build(nowl,l,mid);
    build(nowr,mid+1,r);
    pushup(now);
}

void pt_update(int now,int l,int r,int goal,ll ad,ll mu)
{
    if(goal<l||goal>r)return;
    if(l==r){ma(now)=sum(now)=Mo(sum(now)*mu+ad);return;}
    pushdown(now,l,r);
    int mid=l+r>>1;
    pt_update(nowl,l,mid,goal,ad,mu);
    pt_update(nowr,mid+1,r,goal,ad,mu);
    pushup(now);
}

void inr_update(int now,int l,int r,int x,int y,ll ad,ll mu)
{
	if(l>y||r<x)return;
	if(l>=x&&r<=y){
		ad(0)=ad;mu(0)=mu;
		pushdown_(now,l,r,0);
		return;
	}
	pushdown(now,l,r);
	int mid=l+r>>1;
	inr_update(nowl,l,mid,x,y,ad,mu);
	inr_update(nowr,mid+1,r,x,y,ad,mu);
	pushup(now);
}

void find(int now,int l,int r,int x,int y)
{
	if(l>y||r<x)return;
	if(l>=x&&r<=y){
		Ma=max(Ma,ma(now));
		Sum=Mo(Sum+sum(now));
		return;
	}
	pushdown(now,l,r);
	int mid=l+r>>1;
	find(nowl,l,mid,x,y);
	find(nowr,mid+1,r,x,y);
}

void ask(int l,int r)
{
	Ma=Sum=0;
	find(1,1,n,l,r);
}

int main()
{
    read(&n);read(&mo);
    for(int i=1;i<=n;i++)
    	read(&a[i]);
    build(1,1,n);
    read(&m);
    while(m--){
    	read(&x);read(&l);read(&r);
    	if(x==1){
    		read(&y);
    		inr_update(1,1,n,l,r,0,y);
		}else if(x==2){
			read(&y);
			inr_update(1,1,n,l,r,y,1);
		}else{
			ask(l,r);
			printf("%lld\n",Sum);
		}
	}
}
