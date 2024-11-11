#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, M = 4e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
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

int T, n, m, f[N][M], ans, c[N], w[N], d[N];
vector<int > es[N];

namespace VD {
    int sz[N], msz[N], vis[N], dfn[N], dfn_[N], pt[N], tim, q[M];
    inline void init(int u, int pre) { sz[u] = 1; for (auto &v : es[u]) if (v ^ pre) init(v, u), sz[u] += sz[v]; }
    inline int getG(int u, int pre, int n) {
        msz[u] = 0;
        for (auto v : es[u]) if (!vis[v] && v ^ pre) {
            cmax(msz[u], sz[v]);
            if (v = getG(v, u, n)) return sz[u] = n - msz[u], v;
        }
        return max(msz[u], n - sz[u]) <= n / 2? sz[u] = n, u: 0;
    }
    inline void dfs0(int u, int pre) {
        pt[dfn[u] = ++tim] = u;
        for (auto &v : es[u]) if (!vis[v] && v ^ pre) dfs0(v, u);
        dfn_[u] = tim;
    }
    inline void calc() {
        memset(f[tim + 1], 0, sizeof f[tim + 1]);
        rFor (i, tim, 1) {
            int u = pt[i];
            memcpy(f[i], f[dfn_[u] + 1], sizeof f[i]);
            For (r, 0, c[u] - 1) {
                int h = 1, t = 0;
                For (j, 0, (m - r) / c[u]) {
                    while (h <= t && j - q[h] > d[u]) h++;
                    if (h <= t) cmax(f[i][j * c[u] + r], f[i + 1][q[h] * c[u] + r] + (j - q[h]) * w[u]);
                    while (h <= t && f[i + 1][q[t] * c[u] + r] - q[t] * w[u] <= f[i + 1][j * c[u] + r] - j * w[u]) t--;
                    q[++t] = j;
                }
            }
        }
        For (j, 0, m) cmax(ans, f[1][j]);
    }
    inline void Divide(int u) {
        u = getG(u, 0, sz[u]); vis[u] = 1;
        tim = 0; dfs0(u, 0); cerr << u; calc();
        for (auto &v : es[u]) if (!vis[v]) Divide(v);
    }
}
using namespace VD;

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n >> m;
        For (i, 1, n) io >> w[i];
        For (i, 1, n) io >> c[i];
        For (i, 1, n) io >> d[i];
        int u, v;
        For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
        init(1, 0); Divide(1);
        printf("%d\n", ans);
        For (i, 1, n) es[i].resize(0), vis[i] = 0;
    }

    return 0;
}