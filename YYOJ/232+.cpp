#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

ll a[N],tr[4*N],n,q,x,y,z,res;

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
    tr[now]=tr[now<<1]+tr[now<<1|1];
}

void build(int now,int l,int r)
{
    if(l==r){tr[now]=a[l];return;}
    int mid=l+r>>1;
    build(now<<1,l,mid);
    build(now<<1|+1,mid+1,r);
    pushup(now);
}

void update(int now,int l,int r,int goal,ll ad)
{
    if(goal<l||goal>r)return;
    if(l==r){tr[now]+=ad;return;}
    int mid=l+r>>1;
    update(now<<1,l,mid,goal,ad);
    update(now<<1|1,mid+1,r,goal,ad);
    pushup(now);
}

void find(int now,int l,int r,int x,int y)
{
    if(l>y||r<x)return;
    if(x<=l&&r<=y){res+=tr[now];return;}
    int mid=l+r>>1;
    find(now<<1,l,mid,x,y);
    find(now<<1|1,mid+1,r,x,y);
}

int main()
{
    read(&n);read(&q);
    for(int i=1;i<=n;i++)
        read(&a[i]);
    build(1,1,n);
    while(q--){
        read(&x);read(&y);read(&z);
        if(x==1)
            update(1,1,n,y,z);
        else{
            res=0;
            find(1,1,n,y,z);
            printf("%lld\n",res);
        }
    }
}
