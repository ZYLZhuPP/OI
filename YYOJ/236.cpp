#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

int n,x,y,l,r,q,k;
ll bit[N],Bit[N];

ll lowbit(ll x)
{
    return x&-x;
}

void norm_update(ll* bit,int k,ll ad)//normal
{
    for(;k<=n;k+=lowbit(k))
        bit[k]+=ad;
}

void inr_update(int l,int r,ll ad)//interval
{
    norm_update(bit,l,ad);
    norm_update(Bit,l,ad*l);
    r++;
    norm_update(bit,r,-ad);
    norm_update(Bit,r,-ad*r);
}

void pt_update(int k,ll ad)//point
{
    inr_update(k,k,ad);
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
    for(;k>0;k-=lowbit(k))
        sum-=Bit[k];
    return sum;
}

int main()
{
    scanf("%d%d",&n,&q);
    while(q--){
        scanf("%d",&k);
        if(k==1){
            scanf("%d%d",&l,&r);
            inr_update(l,r,1);
        }else{
            scanf("%d",&x);
            printf("%lld\n",getnum(x)%2);
        }
    }
    return 0;
} 
