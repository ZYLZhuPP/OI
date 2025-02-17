#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5; 

typedef long long ll;

template<class C> inline bool chkmax(C &x, const C &y){return x<y? x=y, 1: 0;}

struct Edge {
    ll to, w;
};
vector<Edge > es[N];

ll n, u, v, w, ans, f[N];

#define gc() getchar()

template<class C>
inline bool read(C &x) {
    x=0;
    ll f=1;
    char c=gc();
    for(; !isdigit(c); c=gc()) 
        if(!(c^EOF)) return 0;
        else if(!(c^45)) f=-1;
    for(; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48);
    x*=f;
    return 1;
}

void dfs(ll u, ll pre) {
    ll siz = es[u].size();
    for (ll i = 0; i < siz; i++) {
        ll v = es[u][i].to;
        dfs(v, u);
        chkmax(f[u], f[v] + es[u][i].w);
    }
    for (ll i = 0; i < siz; i++) {
        ll v = es[u][i].to;
        if (f[v] + es[u][i].w < f[u]) ans += f[u] - (f[v] + es[u][i].w);
    }
}

int main() {
    read(n);
    for (ll i = 0; i < n-1; i++){
        read(u); read(v); read(w);
        es[u].push_back({v, w}); 
    }
    
    dfs(1, 1);
    
    printf("%lld", ans);
    return 0;
}

