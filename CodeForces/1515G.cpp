#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;
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

int n, m, q, dfn[N], low[N], tim, co[N], color, stk[N], top, vis[N];
ll dis[N], g[N];
vector<array<int, 2 > > es[N];

inline void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &[v, w] : es[u])
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    if (dfn[u] == low[u]) {
        color++;
        do co[stk[top]] = color;
        while (stk[top--] ^ u);
    }
}

inline void dfs(int u) {
    vis[u] = 1;
    for (auto &[v, w] : es[u]) if (co[v] == co[u]) {
        if (!vis[v]) dis[v] = dis[u] + w, dfs(v);
        else g[co[u]] = __gcd(g[co[u]], dis[u] + w - dis[v]);
    }
}

int main() {
    io >> n >> m;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, es[u].pb({v, w});
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    For (i, 1, n) if (!vis[i]) dfs(i);
    io >> q;
    ll s, t;
    while (q--) {
        io >> u >> s >> t;
        puts(s % __gcd(t, g[co[u]])? "No": "Yes");
    }

    return 0;
}
