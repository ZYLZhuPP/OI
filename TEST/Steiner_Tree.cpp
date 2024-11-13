#include<bits/stdc++.h>
using namespace std;

#define nd second
#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105, S = 1 << 10;
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

int n, m, K, f[S][N], vis[N], ans = 1e9;
vector<array<int, 2 > > es[N];

inline void Dij(int dis[]) {
    priority_queue<pair<int, int > > q;
    For (i, 1, n) q.push({-dis[i], i}), vis[i] = 0;
    while (!q.empty()) {
        int u = q.top().nd; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w] : es[u]) if (cmin(dis[v], dis[u] + w)) q.push({-dis[v], v});
    }
}

int main() {
    io >> n >> m >> K;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    memset(f, 31, sizeof f);
    For (i, 0, K - 1) io >> u, f[1 << i][u] = 0;
    For (s, 1, (1 << K) - 1) {
        for (int t = s & (s - 1); t > (s ^ t); t = (t - 1) & s) For (i, 1, n) cmin(f[s][i], f[t][i] + f[s ^ t][i]);
        Dij(f[s]);
    }
    For (i, 1, n) cmin(ans, f[(1 << K) - 1][i]);
    printf("%d", ans);

    return 0;
}
