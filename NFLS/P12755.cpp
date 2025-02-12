#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 1e9 + 7, inv2 = 5e8 + 4;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
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

int n, m, L, R, fa[N][17], f[N], a[N], ans;
vector<int > es[N];

namespace VD {
    int sz[N], msz[N], vis[N], dep[N], g[N];
    vector<int > tot, cnt[N];
    inline void init(int u, int pre) { sz[u] = 1; for (auto &v : es[u]) if (v ^ pre) init(v, u), sz[u] += sz[v]; }
    inline int getG(int u, int pre, int n) {
        msz[u] = 0;
        for (auto v : es[u]) if (!vis[v] && v ^ pre) {
            cmax(msz[u], sz[v]);
            if (v = getG(v, u, n)) return sz[u] = n - msz[u], v;
        }
        return max(msz[u], n - sz[u]) <= n / 2? sz[u] = n, u: 0;
    }
    inline void dfs0(int u, int pre, vector<int > &cnt) {
        g[u] = 0; dep[u] = dep[pre] + 1; if ((int)cnt.size() <= dep[u]) cnt.pb(1); else cnt[dep[u]]++;
        for (auto &v : es[u]) if (!vis[v] && v ^ pre) dfs0(v, u, cnt);
    }
    inline int query(const vector<int > &cnt, const int &x) { return x>(int)cnt.size()? cnt.back(): x>0? cnt[x - 1]: 0; }
    inline void dfs(int u, int pre, int rt) {
        g[u] = query(tot, R - dep[u]) - query(tot, L - dep[u] - 1) - query(cnt[rt], R - dep[u]) + query(cnt[rt], L - dep[u] - 1);
        for (auto &v : es[u]) if (!vis[v] && v ^ pre) dfs(v, u, pre? rt: v), add(g[u], g[v]);
        if (!pre) mul(g[u], inv2), add(g[u], L == 1);
        add(f[u], g[u]);
    }
    inline void Divide(int u) {
        u = getG(u, 0, sz[u]); vis[u] = 1;
        tot.resize(0); dfs0(u, 0, tot); int s = 0; for (auto &x : tot) x = (s += x);
        cnt[u] = {1};
        for (auto &v : es[u]) if (!vis[v]) { cnt[v] = {0}; dfs0(v, u, cnt[v]); int s = 0; for (auto &x : cnt[v]) x = (s += x); }
        dfs(u, 0, u);
        for (auto &v : es[u]) if (!vis[v]) Divide(v);
    }
}
using namespace VD;

inline int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 16, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 16, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int main() {
    freopen("sumsum.in", "r", stdin);
    freopen("sumsum.out", "w", stdout);
    dep[0] = -1;
    io >> n >> m >> L >> R;
    For (i, 1, n) io >> a[i];
    For (i, 2, n) io >> fa[i][0], es[fa[i][0]].pb(i), es[i].pb(fa[i][0]);
    For (j, 1, 16) For (i, 1, n) fa[i][j] = fa[fa[i][j - 1]][j - 1];
    init(1, 0); Divide(1);
    For (i, 1, n) add(ans, ml(f[i], a[i])), add(f[i], f[fa[i][0]]), dep[i] = dep[fa[i][0]] + 1;
    while (m--) {
        int u, v, d;
        io >> u >> v >> d;
        int x = lca(u, v);
        add(ans, ml(d, mo(mo(f[u] + f[v]) - mo(f[x] + f[fa[x][0]]))));
        printf("%d\n", ans);
    }

    fclose(stdin); fclose(stdout);
    return 0;
}
