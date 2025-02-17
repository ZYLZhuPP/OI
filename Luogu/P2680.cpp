#include<bits/stdc++.h>
using namespace std;

const int N=3e5+5; 
const int logN=20;

struct XX{
    int u,v,lca,s;
}q[N];

int n,m,u,v,w,va[N],p,L,R,ans;
int tr[N];
int dep[N],s[logN][N],f[logN][N],lg2[N];
int head[N],nxt[2*N],to[2*N],val[2*N],t;
int in[N],out[N],tim;

#define gc() getchar()

template<class T>
inline void read(T &x)
{
    x=0;
    int f=1;
    char ch=gc();
    for(;!isdigit(ch);ch=gc())
        if(!(ch^'-'))
            f=-1;
    for(;isdigit(ch);ch=gc())
        x=(x<<3)+(x<<1)+(ch^48);
    x*=f;
}

int lowbit(int x){return x&-x;}
void add(int,int,int);
void Dfs(int,int,int);
void init();
bool cmp(XX,XX);
int Lca(int,int,int);
void update(int,int);
int getpresum(int);
int getsum(int);
int dfs(int,int);

int main()
{
    read(n);read(m);
    for(int i=1;i<n;i++){
        read(u);read(v);read(w);
        add(u,v,w);
        add(v,u,w);
    }
    init();
    for(int i=1;i<=m;i++){
        read(q[i].u);read(q[i].v);
        q[i].lca=Lca(i,q[i].u,q[i].v);
    }
    sort(q+1,q+m+1,cmp);
    while(L<=R){
        memset(tr,0,sizeof(tr));
        int mid=L+R>>1;
        p=-1;
        for(int i=1;i<=m;i++){
            if(q[i].s>mid){
                update(in[q[i].u],1);
                update(in[q[i].v],1);
                update(in[q[i].lca],-2);
                p=i;
            }else
                break;
        }
        int ma;
        if(p^-1)
            ma=max(dfs(q[p].u,q[p].lca),dfs(q[p].v,q[p].lca));
        if(q[1].s-ma<=mid||p==-1){
            ans=mid;
            R=mid-1;
        }else
            L=mid+1;
    }
    printf("%d",ans);
    return 0;
}

void update(int id,int ad)
{
    for(;id<=n;id+=lowbit(id))
        tr[id]+=ad;
}

int getpresum(int id)
{
    int res=0;
    for(;id;id-=lowbit(id))
        res+=tr[id];
    return res;
}

int getsum(int u)
{
    return getpresum(out[u])-getpresum(in[u]-1);
} 

int dfs(int u,int pre)
{
    if(u==pre)
        return 0;
    return max(getsum(u)^p?0:va[u],dfs(f[0][u],pre));
}

bool cmp(XX X,XX Y)
{
    return X.s>Y.s;
}

int Lca(int id,int u,int v)
{
    int &res=q[id].s;
    if(dep[u]<dep[v])
        swap(u,v);
    int x=dep[u]-dep[v];
    for(;x;x-=lowbit(x)){
        res+=s[lg2[lowbit(x)]][u];
        u=f[lg2[lowbit(x)]][u];
    }
    if(u==v){
        R=max(R,res); 
        return u;
    }
    for(int i=lg2[dep[u]]+1;i>=0;i--)if(f[i][u]^f[i][v]){
        res+=s[i][u]+s[i][v];
        u=f[i][u];
        v=f[i][v];
    }
    res+=s[0][u]+s[0][v];
    R=max(R,res);
    return f[0][u];
}

void add(int u,int v,int w)
{
    nxt[++t]=head[u];
    to[t]=v;
    val[t]=w;
    head[u]=t;
}

void Dfs(int u,int pre,int deep)
{
    in[u]=++tim;
    dep[u]=deep;
    f[0][u]=pre;
    s[0][u]=va[u];
    for(int i=1;i<=lg2[deep];i++){
        f[i][u]=f[i-1][f[i-1][u]];
        s[i][u]=s[i-1][u]+s[i-1][f[i-1][u]];
    }    
    for(int i=head[u];i;i=nxt[i])if(to[i]^pre){
        int v=to[i];
        va[v]=val[i];
        Dfs(v,u,deep+1);
    }
    out[u]=tim;
}

void init(){
    for(int i=2;i<=n;i++)
        lg2[i]=lg2[i>>1]+1;
    Dfs(1,0,0);
}
