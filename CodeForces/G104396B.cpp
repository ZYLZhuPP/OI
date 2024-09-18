#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll inf = 1e16;
const int N = 2e3 + 5;
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

int n, m, dfn[N], low[N], tim, co[N], color, stk[N], top;
int no[N], vis[N], inq[N];
ll dis[N], Dis[N][N];
vector<int > pt[N];
vector<pair<int , int > > es[N], G[N];

inline void SPFA(int c) {
    queue<int > q;
    for (auto &u : pt[c]) dis[u << 1] = dis[u << 1 | 1] = 0, q.push(u << 1), q.push(u << 1 | 1), inq[u << 1] = inq[u << 1 | 1] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for (auto &[v, w] : G[u]) if (cmin(dis[v], dis[u] + w)) if (!inq[v]) q.push(v), inq[v] = 1;
    }
}

inline void Dij(int rt, int c) {
    priority_queue<pair<ll, int > > q;
    for (auto &u : pt[c]) Dis[rt][u << 1] = Dis[rt][u << 1 | 1] = inf, vis[u << 1] = vis[u << 1 | 1] = 0;
    Dis[rt][rt] = 0; q.push({0, rt});
    while (!q.empty()) {
        int u = q.top().nd; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w0] : G[u]) {
            ll w = w0 + dis[u] - dis[v];
            if (cmin(Dis[rt][v], Dis[rt][u] + w)) q.push({-Dis[rt][v], v});
        }
    }
    for (auto &u : pt[c]) Dis[rt][u] -= dis[rt] - dis[u];
}

inline void Johnson(int c) {
    SPFA(c);
    for (auto &u : pt[c]) Dij(u << 1, c);
}

inline bool dfs_spfa(int u) {
    vis[u] = 1;
    for (auto &[v, w] : es[u]) if (co[v] == co[u] && cmin(dis[v], dis[u] + w)) if (vis[v] || dfs_spfa(v)) return 1;
    vis[u] = 0;
    return 0;
}

inline void dfs(int u) {
    vis[u] = 1;
    for (auto &[v, w] : G[u]) if (!vis[v]) dfs(v);
}

inline void solve(int rt, int c) {
    for (auto &u : pt[c]) dis[u] = inf, vis[u] = 0;
    dis[rt] = 0;
    bool flag = dfs_spfa(rt);
    for (auto &u : pt[c]) for (auto &[v, w] : es[u]) if (co[v] == c) 
        G[u << 1].pb({v << 1 | (w & 1), w}), G[u << 1 | 1].pb({v << 1 | !(w & 1), w});
    for (auto &u : pt[c]) {
        for (auto &v : pt[c]) vis[v << 1] = vis[v << 1 | 1] = 0;
        dfs(u << 1);
        if (!vis[u << 1 | 1]) no[u] = 1;
        else if (flag) no[u] = -1;
    }
    if (flag) return;
    Johnson(c);
}

inline void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &[v, w] : es[u]) {
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        color++;
        do co[stk[top]] = color, pt[color].pb(stk[top]);
        while (stk[top--] ^ u);
        solve(u, color);
    }
}

int main() {
    io >> n >> m;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, u++, v++, es[u].pb({v, w});
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    For (i, 1, n) if (no[i] == 1) puts("Battle with the crazy Honkai"); else if (no[i] == -1) puts("Haha, stupid Honkai"); else printf("%lld\n", Dis[i << 1][i << 1 | 1]);

    return 0;
}
