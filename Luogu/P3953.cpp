#include<bits/stdc++.h>
using namespace std;

#define nd second
#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
int Mo;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
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

int n, m, T, K, dis[N], f[N][55];
bool vis[N], in[N][55];
vector<pair<int, int > > G[N], G_[N];

inline void Dij(int rt) {
    memset(dis, 63, sizeof dis);
    memset(vis, 0, sizeof vis);
    priority_queue<pair<int, int > > q;
    dis[rt] = 0; q.push({0, rt});
    while (!q.empty()) {
        int u = q.top().nd; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w] : G_[u]) if (!vis[v] && cmin(dis[v], dis[u] + w)) q.push({-dis[v], v});
    }
}

inline int dfs(int u, int k) {
    if (in[u][k]) return -1;
    if (~f[u][k]) return f[u][k];
    in[u][k] = 1;
    int res = 0;
    for (auto &[v, w] : G[u]) {
        int k_ = k + dis[u] - w - dis[v];
        if (k_ < 0 || k_ > K) continue;
        int x = dfs(v, k_);
        if (!~x) return -1;
        add(res, x);
    }
    in[u][k] = 0;
    return f[u][k] = res;
}

int main() {
    io >> T;
    while (T--) {
        memset(f, -1, sizeof f);
        memset(in, 0, sizeof in);
        io >> n >> m >> K >> Mo;
        int u, v, w;
        For (i, 1, m) io >> u >> v >> w, G[u].pb({v, w}), G_[v].pb({u, w});
        G[n].pb({n + 1, 0}); G_[n + 1].pb({n, 0});
        Dij(++n);
        For (i, 0, K) f[n][i] = 1;
        printf("%d\n", dfs(1, K));
        For (i, 1, n) G[i].resize(0), G_[i].resize(0);
    }

    return 0;
}
