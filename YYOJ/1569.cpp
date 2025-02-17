#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

template<class T> inline bool chkmax(T &x, const T &y) {return x<y? x=y, 1: 0;}

struct Edge {
    int to;
    ll w;
};
vector<Edge > es[N];

ll n, T, w, ans, f[N][3];

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
}io;

void dfs(int u, int pre) {
    f[u][0] = f[u][1] = f[u][2] = 0;
    
    for (auto &e : es[u]) if (pre ^ e.to) {
        int v = e.to;
        dfs(v, u);
        
        ll w = e.w, w1 = w - !(w & 1), w2 = w - (w & 1);
        if (w2) chkmax(f[u][2], f[u][2] + f[v][0] + w2);
        chkmax(f[u][2], f[u][1] + f[v][1] + w1);
        if (w2) chkmax(f[u][2], f[u][0] + f[v][2] + w2);
        if (w2) chkmax(f[u][1], f[u][1] + f[v][0] + w2);
        chkmax(f[u][1], f[u][0] + f[v][1] + w1);
        if (w2) chkmax(f[u][0], f[u][0] + f[v][0] + w2);
    }
    
    chkmax(ans, f[u][0]), chkmax(ans, f[u][1]), chkmax(ans, f[u][2]);
}

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n;
        for (int i = 1; i <= n; ++i) vector<Edge > ().swap(es[i]); 
        int u, v;
        for (int i = 1; i < n; i++) {
            io >> u >> v >> w;
            es[u].push_back({v, w});
            es[v].push_back({u, w});
        }
        dfs(1, 0);
        
        printf("%lld\n", ans);
    }
    
    return 0; 
}


