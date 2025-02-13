#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e3 + 5, inf = 1e9;
template<class C> inline bool cmin(C &x, const C &y) {  return y<x? x=y, 1: 0; }

struct IO {
	char c; int f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, in[N], vis[N], inq[N];
int dis[N], Dis[N][N];
vector<pair<int , int > > G[N];

inline void SPFA() {
    queue<int > q;
    For (i, 1, n) dis[i] = 0, q.push(i), inq[i] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for (auto &[v, w] : G[u]) if (cmin(dis[v], dis[u] + w)) if (!inq[v]) q.push(v), inq[v] = 1;
    }
}

inline void Dij(int rt) {
    priority_queue<pair<int, int > > q;
    For (i, 1, n) Dis[rt][i] = inf, vis[i] = 0;
    Dis[rt][rt] = 0; q.push({0, rt});
    while (!q.empty()) {
        int u = q.top().nd; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w0] : G[u]) {
            int w = w0 + dis[u] - dis[v];
            if (cmin(Dis[rt][v], Dis[rt][u] + w)) q.push({-Dis[rt][v], v});
        }
    }
}

inline void Johnson() {
    SPFA();
    For (i, 1, n) Dij(i);
}

inline bool dfs_spfa(int u) {
    vis[u] = in[u] = 1;
    for (auto &[v, w] : G[u]) if (cmin(dis[v], dis[u] + w)) if (in[v] || dfs_spfa(v)) return 1;
    in[u] = 0;
    return 0;
}

int main() {
    io >> n >> m;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, G[u].pb({v, w});
    For (i, 1, n) dis[i] = inf;
    For (i, 1, n) if (!vis[i] && dfs_spfa(i)) { puts("-1"); return 0; }
    Johnson();
    For (i, 1, n) {
        ll ans = 0;
        For (j, 1, n) ans += 1ll * j * (Dis[i][j]<inf? Dis[i][j] - dis[i] + dis[j]: inf);
        printf("%lld\n", ans);
    }

    return 0;
}
