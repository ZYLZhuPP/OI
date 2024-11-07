#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

vector<int > G[N], T[N];
int n, m, K, R, dfn[N], low[N], color, tim, co[N], dep[N], stk[N], top, fa[N][20], s[N], Mx, mx;
unordered_map<int, bool > mp[N];

inline void Tarjan(int u, int pre) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : G[u]) if (v ^ pre) {
        if (!dfn[v]) Tarjan(v, u), cmin(low[u], low[v]);
        else cmin(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        color++;
        do co[stk[top]] = color;
        while (stk[top--] ^ u);
    }
}

inline void init(int u, int pre) {
    dep[u] = dep[pre] + 1; fa[u][0] = pre;
    For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &v : T[u]) if (v ^ pre) init(v, u);
}

inline int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 19, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 19, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

inline void dfs(int u, int pre) {
    for (auto &v : T[u]) if (v ^ pre) dfs(v, u), s[u] += s[v];
    cmax(mx, s[u]);
    if (mx > Mx) swap(Mx, mx);
}

int main() {
    io >> n >> m >> K >> R;
    int u, v;
    For (i, 1, m) io >> u >> v, G[u].pb(v), G[v].pb(u);
    Tarjan(1, 0);
    For (u, 1, n) for (auto &v : G[u]) if (co[u] ^ co[v] && !mp[co[u]][co[v]]) T[co[u]].pb(co[v]), mp[co[u]][co[v]] = 1;
    init(1, 0);
    while (K--) {
        io >> u >> v;
        u = co[u]; v = co[v];
        int f = lca(u, v);
        s[u]++; s[v]++; s[f] -= 2;
    }
    dfs(1, 0);
    printf("%d", Mx + (R>1? mx: 0));

    return 0;
}
