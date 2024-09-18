#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e12;
const int N = 3e4 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, x, y, s, vis[N], deg[N];
ll dis[N];
vector<pair<int, int > > G[N], T[N];
vector<int > pt[N];
int dfn[N], low[N], tim, co[N], color, stk[N], top;

void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &[v, w] : G[u])
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    for (auto &[v, w] : T[u])
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        color++;
        do co[stk[top]] = color, pt[color].pb(stk[top]);
        while (stk[top--] ^ u);
    }
}

inline void Dij(int c) {
    priority_queue<pair<ll, int > > q;
    for (auto &u : pt[c]) q.push({-dis[u], u});
    while (!q.empty()) {
        int u = q.top().nd; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w] : G[u]) if (co[v] == c && cmin(dis[v], dis[u] + w)) q.push({-dis[v], v});
        for (auto &[v, w] : T[u]) cmin(dis[v], dis[u] + w);
    }
}

int main() {
    io >> n >> x >> y >> s;
    int u, v, w;
    For (i, 1, x) io >> u >> v >> w, G[u].pb({v, w}), G[v].pb({u, w});
    For (i, 1, y) io >> u >> v >> w, T[u].pb({v, w});
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    memset(dis, 31, sizeof dis); dis[s] = 0;
    rFor (i, color, 1) Dij(i);
    For (i, 1, n) if (dis[i] < INF) printf("%lld\n", dis[i]); else puts("NO PATH");

    return 0;
}
