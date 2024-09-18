#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

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
    inline bool operator ~ () { return ~c; }
} io;

int n, K, siz[N], id[N];
ll g[N], len[N], le[N], f[N], up[N];
vector<pair<int, int > > es[N];

void dfs0(int u, int pre) {
    for (auto &[v, w] : es[u]) if (v ^ pre) {
        dfs0(v, u); siz[u] += siz[v];
        if (!siz[v]) g[u] += g[v];
        else {
            g[u] += g[v] + 2 * w;
            if (len[v] + w > len[u]) le[u] = len[u], len[u] = len[v] + w, id[u] = v;
            else if (len[v] + w > le[u]) le[u] = len[v] + w;
        }
    }
}

void dfs(int u, int pre, int w0) {
    if (siz[u] < K) g[u] = g[pre] + (!siz[u]? 2 * w0: 0);
    f[u] = g[u] - max(up[u], len[u]);
    for (auto &[v, w] : es[u]) if (v ^ pre) {
        up[v] = max(siz[u]-siz[v]>0? (v^id[u]? len[u]: le[u]) + w: 0, siz[u]<K? up[u] + w: 0);
        dfs(v, u, w);
    }
}

int main() {
    io >> n >> K;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    For (i, 1, K) io >> u, siz[u] = 1;
    dfs0(1, 0); dfs(1, 0, 0);
    For (i, 1, n) printf("%lld\n", f[i]);

    return 0;
}