#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=3e5+5;
const int logN=20;

struct SMT{
    int lson=-1,rson=-1,sum;
    ll id=-1;
}smt[3*N*logN];

#define ls(x) smt[x].lson
#define rs(x) smt[x].rson
#define sum(x) smt[x].sum
#define id(x) smt[x].id

int n,m,q,n_,nn,nn_,x,y,t;
ll z,res,ans;
ll tail[N];

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

ll getsum(int p,int k,int l,int r)
{
    if(k^-1)
        return sum(k);
    if(p^n_)
        return min(r,m-1)-min(l,m)+1;
    return min(r,n)-min(l,n+1)+1;
}

ll getid(int p,int k,int l){
    if(id(k)^-1)
        return id(k);
    if(p^n_)
        return (ll)m*(p-1)+l;
    return (ll)l*m;
}

void add_smt(int p,int &k,int l,int r)
{
    if(k==-1)
        sum(k=++t)=getsum(p,-1,l,r);
} 

void pushup(int p,int k,int l,int r)
{
    int mid=l+r>>1;
    sum(k)=getsum(p,ls(k),l,mid)+getsum(p,rs(k),mid+1,r);
}

void find(int p,int &k,int l,int r,int goal,int sum)
{
    if(sum+getsum(p,k,l,r)<goal||goal<=sum)
        return;
    add_smt(p,k,l,r);
    if(l==r){
        res=l;
        return;
    }
    int mid=l+r>>1;
    find(p,ls(k),l,mid,goal,sum);
    find(p,rs(k),mid+1,r,goal,sum+getsum(p,ls(k),l,mid));
}

void update(int p,int &k,int l,int r,int goal,int sum,ll id)
{
    if(r<goal||goal<l)
        return;
    add_smt(p,k,l,r);
    if(l==r){
        sum(k)=sum;
        res=getid(p,k,l);
        id(k)=id;
        return;
    }
    int mid=l+r>>1;
    update(p,ls(k),l,mid,goal,sum,id);
    update(p,rs(k),mid+1,r,goal,sum,id);
    pushup(p,k,l,r);
}

void init()
{
    for(int i=1;i<=n;i++)
        tail[i]=sum(++t)=m-1;
    tail[n_]=sum(++t)=n;
}

int main()
{
    read(&n);read(&m);read(&q);
    n_=n+1;
    nn=m+q-1;
    nn_=n+q;
    init();
    while(q--){
        read(&x);read(&y);
        if(y^m){
            find(x,x,1,nn,y,0);z=res;
            update(x,x,1,nn,z,0,-1);ans=res;
            tail[x]++;
            find(n_,n_,1,nn_,x,0);z=res;
            update(n_,n_,1,nn_,z,0,-1);z=res;
            tail[n_]++;
            update(x,x,1,nn,tail[x],1,z);
        }else{
            find(n_,n_,1,nn_,x,0);z=res;
            update(n_,n_,1,nn_,z,0,-1);ans=res;
            tail[n_]++;
        }
        update(n_,n_,1,nn_,tail[n_],1,ans);
        printf("%lld\n",ans);
    }
} 
