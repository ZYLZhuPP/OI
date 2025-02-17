#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y) { return x<=y? x=y, 1: 0; }

const int N = 5e5 + 5;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) f|=-!(c^45);
        for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct Edge {
    int to;
};
vector<Edge > es[N];

int n, a[N], ans, cnt;
double f[N];

void dfs(int u, double sum) {
    f[u] = sum + log(a[u]);
    for (auto &e: es[u]) {
        int v = e.to;
        dfs(v, sum + log(es[u].size()));
    }
}

int main() {
    io >> n;
    for (int i = 1; i <= n; i++) 
        io >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v; 
        io >> u >> v;
        es[u].emplace_back((Edge){v});
    } 
    
    dfs(1, 0);
    sort(f+1, f+n+1);
    
    f[0] = -1;
    for (int i = 1; i <= n; i++) {
        if (f[i] - f[i - 1] < 1e-12) {
            cnt++;
            chkmax(ans, cnt);
        } else
            cnt = 1;
    }
    
    printf("%d", n - ans);
    return 0;
} 
