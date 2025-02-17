#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

int n,x,y,q,k;
ll bit[N],a[N],t;

int lowbit(int x)
{
    return x&-x;
}

void update(int k,int ad)
{
    for(;k<=n;k+=lowbit(k))
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
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        update(i,x);
    }
    while(q--){
        scanf("%d%d%d",&k,&x,&y);
        if(k==1)
            update(x,y);
        else 
            a[++t]=getsum(y)-getsum(x-1);
    }
    for(int i=1;i<t;i++)
        printf("%lld\n",a[i]);
    printf("%lld",a[t]);
    return 0;
} 
