#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int T, n, m, K, P, _[N], ans, a[N], g[N][N], W1[N][N], W2[N][N], f[N][15], vis[N], id[N], tot, dep[N];
vector<array<int, 3 > > es[N];

inline void solve0(int k, int p, int res) {
    if (k < n) for (auto &[v, w1, w2] : es[k + 1]) if (v > k) mul(res, a[v]^a[k + 1]? w1: w2);
    if (!res || p > K) return;
    if (!k) return add(ans, ml(res, _[p]));
    For (i, 1, p) a[k] = i, solve0(k - 1, p, res);
    a[k] = ++p; solve0(k - 1, p, res);
}

inline void dfs(int u, int pre) {
    f[u][0] = !id[u] && P<K; For (i, 1, P) f[u][i] = !id[u];
    if (id[u]) f[u][a[id[u]]] = 1;
    for (auto &[v, w1, w2] : es[u]) if (dep[v] == dep[u] + 1) dfs(v, u);
    for (auto &[v, w1, w2] : es[u]) if (v ^ pre) {
        if (dep[v] == dep[u] + 1) {
            int s = ml(K - P, f[v][0]);
            For (i, 1, P) add(s, f[v][i]);
            For (i, 0, P) mul(f[u][i], mo(ml(w1, s - f[v][i]) + ml(w2, f[v][i])));
        } else if (dep[v] < dep[u]) {
            mul(f[u][a[id[v]]], w2);
            For (i, 0, P) if (i ^ a[id[v]]) mul(f[u][i], w1);
            continue;
        }
    }
}

int cnt;
inline void dfs1(int k, int p) {
    if (p > K) return;
    if (!k) {
        P = p;
        dfs(1, 0); cnt++;
        add(ans, ml(K - P, ml(f[1][0], _[P])));
        For (i, 1, P) add(ans, ml(f[1][i], _[P]));
        return;
    }
    For (i, 1, p) a[k] = i, dfs1(k - 1, p);
    a[k] = ++p; dfs1(k - 1, p);
}

inline void dfs0(int u, int pre) {
    vis[u] = 1; dep[u] = dep[pre] + 1;
    for (auto &[v, w1, w2] : es[u]) if (v ^ pre) {
        if (!vis[v]) dfs0(v, u);
        else if (dep[v] > dep[u] && !id[u]) id[u] = ++tot;
    }
}

inline void solve1() {
    tot = 0; For (i, 1, n) vis[i] = id[i] = 0;
    dfs0(1, 0);
    cnt = 0;
    dfs1(tot, 0);
}

int main() {
    io >> T;
    while (T--) {
        ans = 0; memset(g, 0, sizeof g);
        io >> n >> m >> K;
        _[0] = 1; For (i, 1, min(n, K)) _[i] = ml(_[i - 1], K - i + 1);
        int u, v, w1, w2;
        For (i, 1, m) {
            io >> u >> v >> w1 >> w2; if (u > v) swap(u, v);
            if (g[u][v]) mul(W1[u][v], w1), mul(W2[u][v], w2);
            else g[u][v] = 1, W1[u][v] = w1, W2[u][v] = w2;
        }
        rFor (u, n, 1) rFor (v, n, u + 1) if (g[u][v]) es[u].pb({v, W1[u][v], W2[u][v]}), es[v].pb({u, W1[u][v], W2[u][v]});
        n<=12? solve0(n, 0, 1): solve1();
        printf("%d\n", ans);
        For (i, 1, n) es[i].resize(0);
    }

    return 0;
}
