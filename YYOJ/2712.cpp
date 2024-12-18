#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
typedef long long ll;
typedef array<ll, 2 > P;
const ll INF = 2e18;
const int N = 1 << 18, inf = 1e9;
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

int T, n, m, S, w[20], d[20][20], s[N], q[20][N], top[20];
ll f[N][20];
P g[20][N];
lf p[20][N];

inline lf K(const P &x, const P &y) { return 1.0 * (x[1] - y[1]) / (x[0] - y[0]); }

inline void build(int k) {
    For (i, 0, S - 1) g[k][i] = {s[i], f[i][k]};
    sort(g[k], g[k] + S);
    For (i, 0, S - 1) {
        if (g[k][i][1] == INF) continue;
        if (i && g[k][i][0] == g[k][i - 1][0]) continue;
        int &t = top[k];
        while (t > 1 && K(g[k][q[k][t]], g[k][q[k][t - 1]]) >= K(g[k][i], g[k][q[k][t]])) t--;
        q[k][++t] = i;
    }
    For (i, 1, top[k] - 1) p[k][i] = K(g[k][q[k][i]], g[k][q[k][i + 1]]);
}

int main() {
    io >> n >> m; S = 1 << n;
    For (i, 1, n) io >> w[i];
    For (i, 1, n) For (j, 1, n) if (i ^ j) d[i][j] = inf;
    int u, v, t;
    For (i, 1, m) io >> u >> v >> t, d[u][v] = t;
    For (k, 1, n) For (i, 1, n) For (j, 1, n) cmin(d[i][j], d[i][k] + d[k][j]);
    For (i, 0, S - 1) For (j, 1, n) {
        f[i][j] = INF;
        if (i >> (j - 1) & 1) s[i] += w[j];
    }
    For (i, 1, n) f[1 << (i - 1)][i] = 0;
    For (i, 0, S - 1) For (j, 1, n) if (f[i][j] < INF)
        For (k, 1, n) if (!(i >> (k - 1) & 1) && d[j][k] < inf) cmin(f[i | 1 << (k - 1)][k], f[i][j] + 1ll * s[i] * d[j][k]);
    For (i, 1, n) build(i);
    io >> T;
    while (T--) {
        io >> t >> u;
        int k = q[u][upper_bound(p[u] + 1, p[u] + top[u], t) - p[u]];
        printf("%lld\n", t * g[u][k][0] - g[u][k][1]);
    }
    
    return 0;
}
