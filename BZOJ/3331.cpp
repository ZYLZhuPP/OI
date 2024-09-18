#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
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

vector<int > G[N], T[N << 1];
int n, m, Q, dfn[N], low[N], tim, tot, stk[N], top, cnt[N << 1], fa[N << 1][20], dep[N << 1];

void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : G[u])
        if (!dfn[v]) {
            Tarjan(v), cmin(low[u], low[v]);
            if (low[v] == dfn[u]) {
                T[++tot].pb(u); T[u].pb(tot);
                do T[tot].pb(stk[top]), T[stk[top]].pb(tot);
                while (stk[top--] ^ v);
            }
        } else cmin(low[u], dfn[v]);
}

inline void dfs0(int u, int pre) {
    dep[u] = dep[pre] + 1; fa[u][0] = pre;
    For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &v : T[u]) if (v ^ pre) dfs0(v, u);
}

inline int lca(int u, int v) {
    if (dep[v] > dep[u]) swap(u, v);
    rFor (i, 19, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 19, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

inline void dfs(int u, int pre) {
    for (auto &v : T[u]) if (v ^ pre) dfs(v, u), cnt[u] += cnt[v];
}

int main() {
    io >> n >> m >> Q;
    int u, v;
    For (i, 1, m) io >> u >> v, G[u].pb(v), G[v].pb(u);
    tot = n; Tarjan(1); dfs0(1, 0);
    while (Q--) {
        io >> u >> v;
        int f = lca(u, v);
        cnt[u]++; cnt[v]++; cnt[f]--; cnt[fa[f][0]]--;
    }
    dfs(1, 0);
    For (i, 1, n) printf("%d\n", cnt[i]);

    return 0;
}
