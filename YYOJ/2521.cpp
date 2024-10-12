#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, V = 1e6 + 5, M = 5e6 + 5, inf = 1e9;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, id[N][2][N], tot, a[N][N], b[N][N];
unordered_map<int, int > g[V];

namespace HLPP {
    struct edge{
        int v,w,rev;
        edge(){}
        edge(int _v,int _w,int _rev){
            v=_v,w=_w,rev=_rev;
        }
    };
    vector<edge>E[V];
    vector<int>q,H,cnt;
    vector<int>flow;
    vector<int>S[V];
    list<int>gap[V];
    vector<list<int>::iterator> ep;
    int s,t,mxH,szH;
    inline void add(int u,int v,int w){
        E[u].push_back(edge(v,w,E[v].size())),
        E[v].push_back(edge(u,0,E[u].size()-1));
    }
    void init_label(){
        q.clear();
        q.resize(tot+1);
        H.assign(tot+2,tot+2);
        H[t]=0;
        int l=0,r=0;
        q[r++]=t;
        while(l<r){
            int x=q[l++];
            for(edge e:E[x])
                if(H[e.v]==tot+2&&E[e.v][e.rev].w)
                    ++cnt[H[q[r++]=e.v]=H[x]+1];
        }
        for(int i=0;i<=tot;++i)gap[i].clear(),S[i].clear();
        for(int i=1;i<=tot;++i)
        if(H[i]<=tot){
            ep[i]=gap[H[i]].insert(gap[H[i]].begin(),i);
            if(flow[i]>0)S[H[i]].push_back(i);
        }
        mxH=szH=H[q[r-1]];
    }
    inline void edge_push(int x,edge &e){
        int w=min(e.w,flow[x]);
        flow[x]-=w,e.w-=w,flow[e.v]+=w,E[e.v][e.rev].w+=w;
        if(flow[e.v]>0&&flow[e.v]<=w)S[H[e.v]].push_back(e.v);
    }
    void push(int x){
        int fx=tot+1,tmp=H[x];
        for(edge& k:E[x]){
            if(k.w<=0)continue;
            if(H[k.v]+1==H[x]){
                edge_push(x,k);
                if(!flow[x])return;
            }
            else fx=min(fx,H[k.v]+1);
        }
        if(cnt[H[x]]<=1){
            for(int i=tmp;i<=mxH;gap[i].clear(),++i)
                for(int j:gap[i])--cnt[H[j]],H[j]=tot+1;
            mxH=tmp-1;
            return;
        }
        --cnt[tmp];
        ep[x]=gap[tmp].erase(ep[x]);
        H[x]=fx;
        if(fx==tot+1)return;
        ++cnt[fx];
        ep[x]=gap[fx].insert(gap[fx].begin(),x);
        mxH=max(szH=fx,mxH);
        S[fx].push_back(x);
    }
    int maxflow(){
        H.assign(tot+1,0);H[s]=tot+1;
        cnt.assign(tot+1,0);
        ep.resize(tot+1);
        for(int i=1;i<=tot;++i)
            if(i!=s)ep[i]=gap[H[i]].insert(gap[H[i]].begin(),i);
        cnt[0]=tot;
        flow.resize(tot+1,0);
        flow[s]=inf,flow[t]=-inf;
        for(edge &i:E[s])edge_push(s,i);
        init_label();
        while(szH>=0){
            if(S[szH].empty())--szH;
            else{
                int x=S[szH].back();
                S[szH].pop_back();
                push(x);
            }
        }
        return flow[t]+inf;
    }
}
using namespace HLPP;

inline void Add(int u, int v, const int &w) {
    int x = ++tot, y = ++tot;
    add(v, x, w); add(u, x, w); add(y, u, w); add(x, y, w); add(y, v, w);
}

int main() {
    freopen("in.in", "r", stdin);
    io >> n >> m;
    For (i, 1, n) {
        For (j, 1, m - 1) io >> a[i][j] >> b[i][j];
        io >> a[i][m];
    }
    For (i, 1, m) id[1][0][i] = ++tot, id[n][1][i] = ++tot;
    For (i, 1, n - 1) {
        int x;
        io >> x;
        while (x--) {
            int l1, r1, l2, r2;
            io >> l1 >> r1 >> l2 >> r2;
            int x = ++tot;
            For (j, l1, r1) id[i][1][j] = x;
            For (j, l2, r2) id[i + 1][0][j] = x;
        }
    }
    For (i, 1, n) {
        For (j, 1, m) g[id[i][0][j]][id[i][1][j]] += a[i][j];
        For (j, 1, m - 1) g[id[i][0][j]][id[i][1][j + 1]] += b[i][j];
    }
    For (i, 1, tot) for (auto &[v, w] : g[i]) Add(i, v, w);
    s = ++tot, t = ++tot;
    cerr << tot << endl;
    For (i, 1, m) add(s, id[1][0][i], inf), add(id[n][1][i], t, inf);
    printf("%d", maxflow());

    return 0;
}
