#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 50, Mo = 998244353, inv2 = 499122177;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, m, inv, ans, f[N], g[N], h[N], co[N], a[N][N];
bool vis[N];
vector<int > pt, es[N];

inline void dfs0(int u) {
    vis[u] = 1; pt.pb(u);
    for (auto &v : es[u]) if (!vis[v]) dfs0(v);
}

inline void dfs(int k, int n, int c) {
    if (k == (int)pt.size()) return add(g[n], c), void();
    int c1 = c, c2 = c, u = pt[k];
    for (auto &v : es[u]) if (co[v] == 2) c1 = 2ll * c1 * a[u][v] % Mo; else if (co[v] == 1) c2 = 2ll * c2 * a[v][u] % Mo;
    co[u] = 1; dfs(k + 1, n + 1, c1);
    co[u] = 2; dfs(k + 1, n, c2);
    co[u] = 0;
}

int main() {
    inv = qPow(10000, Mo - 2);
    io >> n >> m;
    For (i, 1, n) For (j, 1, n) if (i ^ j) a[i][j] = inv2;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, mul(w, inv), es[u].pb(v), es[v].pb(u), a[u][v] = w, a[v][u] = mo(1 - w);
    f[0] = 1;
    For (u, 1, n) if (!vis[u]) {
        pt.clear();
        dfs0(u);
        For (i, 0, n) g[i] = h[i] = 0;
        dfs(0, 0, 1);
        For (i, 0, n) For (j, 0, n - i) h[i + j] = (h[i + j] + 1ll * f[i] * g[j]) % Mo;
        For (i, 0, n) f[i] = h[i];
    }
    For (i, 1, n - 1) ans = (ans + 1ll * f[i] * qPow(inv2, i * (n - i))) % Mo;
    ans = ml(ans + 1, qPow(10000, n * (n - 1)));
    printf("%d", ans);

    return 0;
}
