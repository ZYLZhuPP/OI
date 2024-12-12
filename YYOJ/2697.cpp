#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
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

vector<int > G[N], T[N], pt[N];
int n, m, K, fa[N], pa[N], cnt[N], sz[N], rt, ans, vis[N], w[N];
int dfn[N], low[N], tim, tot, stk[N], top;

inline int find(int x) { return pa[x]^x? pa[x] = find(pa[x]): x; }
inline void merge(int x, int y) {
    x = find(x); y = find(y);
    cnt[sz[x]]--; cnt[sz[y]]--;
    pa[y] = x; cnt[sz[x] += sz[y]]++;
}

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

inline void getG(int u, int pre) {
    int mx = 0;
    sz[u] = u <= n;
    for (auto v : T[u]) if (v ^ pre) getG(v, u), sz[u] += sz[v], cmax(mx, sz[v]);
    if (max(mx, n - sz[u]) <= n / 2) rt = u;
}

inline void dfs(int u, int pre) {
    fa[u] = pre; sz[u] = u <= n;
    for (auto &v : T[u]) if (v ^ pre) dfs(v, u), sz[u] += sz[v];
    if (u > n) pt[sz[u]].pb(u);
}

int main() {
    io >> n >> m >> K; tot = n;
    int u, v;
    For (i, 1, m) io >> u >> v, G[u].pb(v), G[v].pb(u);
    Tarjan(1);
    getG(1, 0); if (rt > n) rt = T[rt][0];
    dfs(rt, 0);
    For (i, 1, n) pa[i] = i, sz[i] = 1;
    cnt[1] = n;
    For (i, 1, n - 1) {
        for (auto &u : pt[i]) {
            int n = T[u].size();
            if (n > 2) For (j, 1, n - 1) merge(T[u][j - 1], T[u][j]);
        }
        if (cnt[i] * i == n) add(ans, K? -1: 1);
        vector<int > vec;
        for (auto &u : pt[i]) if ((int)T[u].size() == 2) {
            int f = fa[u];
            if (sz[find(f)] == 1) {
                vis[u] = vis[f] = 1;
                merge(T[u][0], T[u][1]);
                vec.pb(f); w[f] = 1;
            } else w[f] += vis[f];
        }
        if (K && cnt[i] * i + cnt[i + 1] * (i + 1) == n) {
            int x = 1;
            for (auto &u : vec) mul(x, w[u] + (i == 1));
            add(ans, x);
        }
        for (auto &u : pt[i]) if ((int)T[u].size() == 2 && !vis[u]) merge(T[u][0], T[u][1]);
    }
    printf("%d", ans);

    return 0;
}
