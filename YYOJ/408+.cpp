#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

ll a[N],tr[4*N],n,q,x,y,l,r,res;

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

void q_update(int now,int l,int r,int x,int y,ll ad)
{
	if(l>y||r<x)return;
	if(l>=x&&r<=y){tr[now]+=ad;return;}
	int mid=l+r>>1;
	q_update(now<<1,l,mid,x,y,ad);
	q_update(now<<1|1,mid+1,r,x,y,ad);
}

void find(int now,int l,int r,int x)
{
	if(l>x||r<x)return;
	res+=tr[now];
	if(l==r)
		return;
	int mid=l+r>>1;
	find(now<<1,l,mid,x);
	find(now<<1|1,mid+1,r,x);
}

int main()
{
	read(&n);read(&q);
	for(int i=1;i<=n;i++)
		read(&a[i]);
	while(q--){
		read(&x);
		if(x==1){
			read(&l);read(&r);read(&y);
			q_update(1,1,n,l,r,y);
		}else{
			read(&y);
			res=a[y];
			find(1,1,n,y);
			printf("%lld\n",res);
		}
	}
}
