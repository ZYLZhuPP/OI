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

int n, q, K, a[N], mn[N], fa[N];
vector<int > es[N];
vector<array<int, 2 > > qs[N];
vector<array<int, 3 > > Qs[N];

struct mat {
    ll o[3][3];
    mat() { memset(o, 31, sizeof o); }
    mat& operator = (const int &x) {
        For (i, 0, K - 1) o[i][0] = a[x];
        For (i, 0, K - 2) o[i][i + 1] = 0;
        if (K == 3) o[1][1] = mn[x];
        return *this;
    }
    mat operator * (const mat &a) const {
        mat r;
        For (k, 0, K - 1) For (i, 0, K - 1) For (j, 0, K - 1) cmin(r.o[i][j], o[i][k] + a.o[k][j]);
        return r;
    }
} f[N][2], ans[N], _;

inline int find(int x) {
    if (fa[x] == fa[fa[x]]) return fa[x];
    int u = fa[x]; fa[x] = find(u);
    f[x][0] = f[x][0] * f[u][0];
    f[x][1] = f[u][1] * f[x][1];
    return fa[x];
}

inline mat get(int x, int k) { int u = find(x); return u^x? f[x][k]: _; }

inline void dfs(int u, int pre) {
    for (auto &[v, id] : qs[u]) if (fa[v]) Qs[find(v)].pb({pre, v, id}), ans[id].o[0][0] = a[u];
    fa[u] = u; f[u][0] = f[u][1] = u;
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u), fa[v] = u;
    for (auto &[v1, v2, id] : Qs[u]) ans[id] = ans[id] * get(v1, 0) * f[u][0] * get(v2, 1);
}

int main() {
    io >> n >> q >> K;
    For (i, 0, K - 1) _.o[i][i] = 0;
    For (i, 1, n) io >> a[i], mn[i] = 1e9;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u), cmin(mn[u], a[v]), cmin(mn[v], a[u]);
    For (i, 1, q) io >> u >> v, qs[u].pb({v, i}), qs[v].pb({u, i});
    dfs(1, 0);
    For (i, 1, q) printf("%lld\n", ans[i].o[0][0]);

    return 0;
}
