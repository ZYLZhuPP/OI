#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=3e4+5;
const ll INF=LLONG_MAX/2;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
        for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
        return *this;
    }
    inline IO& operator >> (char *x){
        while(c<33) c=gc();
        for(; c>32; c=gc()) (*x++)=c;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct SMT{
    ll ma,sum,ad;
}tr[4*N];

int pot[N];
int root,t,head[N],to[2*N],nxt[2*N];
int fa[N],dep[N],son[N],siz[N],top[N],id[N];
ll w[N];
int end_id[N],end_p[N];
int n,q,Lca;
ll Ma,Sum;
char st[10];

#define nowl now<<1
#define nowr now<<1|1

void add(int u,int v)
{
    nxt[++t]=head[u];
    to[t]=v;
    head[u]=t;
}

void dfs1(int u,int pre,int deep)
{
    fa[u]=pre;
    siz[u]=1;
    dep[u]=deep;
    for(int i=head[u];i;i=nxt[i])if(to[i]^pre){
        int v=to[i];
        dfs1(v,u,deep+1);
        siz[u]+=siz[v];
        if(siz[son[u]]<siz[v])
            son[u]=v;
    }
}

void dfs2(int u)
{
    id[u]=++id[0];
    pot[id[u]]=u;
    if(son[u]){
        int v=son[u];
        top[v]=top[u];
        dfs2(v);
    }
    for(int i=head[u];i;i=nxt[i])if(!top[to[i]]){
        int v=to[i];
        top[v]=v;
        dfs2(v);
    }
    end_id[u]=id[u]+siz[u]-1;
    end_p[u]=pot[end_id[u]];
} 

void init()
{
    dfs1(root,0,0);
    top[root]=root;
    dfs2(root);
}

void pushup(int now)
{
    tr[now].sum=tr[nowl].sum+tr[nowr].sum;
    tr[now].ma=max(tr[nowl].ma,tr[nowr].ma);
}

void pushdown(int now,int l,int r)
{
    int ad=tr[now].ad;
    int mid=l+r>>1;
    tr[nowl].sum+=(mid-l+1)*ad;
    tr[nowl].ma+=ad;
    tr[nowl].ad+=ad;
    tr[nowr].sum+=(r-mid)*ad;
    tr[nowr].ma+=ad;
    tr[nowr].ad+=ad;
    tr[now].ad=0;
}

void build(int now,int l,int r)
{
    if(l==r){
        tr[now].ma=tr[now].sum=w[pot[l]];
        return;
    }
    int mid=l+r>>1;
    build(nowl,l,mid);
    build(nowr,mid+1,r);
    pushup(now);
}

void find(int now,int l,int r,int x,int y)
{
    if(l>y||r<x)
        return;
    if(l>=x&&r<=y){
        Sum+=tr[now].sum;
        Ma=max(Ma,tr[now].ma);
        return;
    }
    pushdown(now,l,r);
    int mid=l+r>>1;
    find(nowl,l,mid,x,y);
    find(nowr,mid+1,r,x,y);
}

void update(int now,int l,int r,int goal,int val)
{
    if(l>goal||r<goal)
        return;
    if(l==r){
        w[pot[l]]=val;
        tr[now].ma=tr[now].sum=val;
        return;
    }
    pushdown(now,l,r);
    int mid=l+r>>1;
    update(nowl,l,mid,goal,val);
    update(nowr,mid+1,r,goal,val);
    pushup(now);
}

void l_query(int u,int v)
{
    Ma=-INF;
    Sum=0;
    int tu=top[u],tv=top[v];
    while(tu^tv){
        if(dep[tu]<dep[tv]){
            swap(u,v);
            swap(tu,tv);
        }
        find(1,1,n,id[tu],id[u]);
        u=fa[tu];
        tu=top[u];
    }
    if(dep[u]>dep[v])
        swap(u,v);
    Lca=u;
    find(1,1,n,id[u],id[v]);
} 

void q_update(int now,int l,int r,int x,int y,int ad)
{
    if(l>y||r<x)
        return;
    if(l>=x&&r<=y){
        tr[now].sum+=(r-l+1)*ad;
        tr[now].ma+=ad;
        tr[now].ad+=ad;
        return;
    }
    pushdown(now,l,r);
    int mid=l+r>>1;
    q_update(nowl,l,mid,x,y,ad);
    q_update(nowr,mid+1,r,x,y,ad);
    pushup(now);
}

void tr_update(int u,int ad)
{
    q_update(1,1,n,id[u],end_id[u],ad);
}

int main()
{
    io>>n;
    root=1;
    for(int i=1;i<n;i++){
        int u,v;
        io>>u>>v;
        add(u,v);
        add(v,u);
    }
    for(int i=1; i<=n; i++) io>>w[i];
    init();
    build(1,1,n);
    io>>q;
    while(q--){
        io>>st; 
        if(st[1]=='H'){
            int u,w;
            io>>u>>w;
            update(1,1,n,id[u],w);
        }else{
            int u,v;
            io>>u>>v;
            l_query(u,v);
            if(st[1]=='M')
                printf("%lld\n",Ma);
            else
                printf("%lld\n",Sum);
        }
    }
}
