#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, w[N], g[N];
ll f[N], sum;
vector<int > es[N];

inline void dfs(int u, int pre) {
    int mx = 0; ll s = 0;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        f[u] += f[v];
        cmin(g[v], w[u]);
        s += g[v];
        cmax(mx, g[v]);
    }
    if (!s) return g[u] = w[u], void();
    f[u] += min(2ll * w[u], s);
    g[u] = max(0ll, min(2ll * w[u] - s, 1ll * w[u]));
}

int main() {
    io >> n;
    For (i, 1, n) io >> w[i], sum += w[i];
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs(1, 0);
    printf("%lld", sum - f[1]);
    
    return 0;
}
