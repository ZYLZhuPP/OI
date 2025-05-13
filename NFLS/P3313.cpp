#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define OVER { puts("NO"); return; }
const int N = 1005;

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

int T, n, f[N], g[N], Rtf[N], Rtg[N], deg[N], a[N][N], dep[N];
bool visf[N][N], visg[N][N], h[N], rtf[N], rtg[N], vis[N];
vector<int > pt[N], es[N], F[N], G[N];
vector<array<int, 2 > > ops;

inline void dfs0(int u) { for (auto &v : F[u]) dep[v] = dep[u] + 1, dfs0(v); }
inline void dfsf(int u, int rt) { visf[rt][u] = 1; for (auto &v : F[u]) dfsf(v, rt); }
inline void dfsg(int u, int rt) { visg[rt][u] = 1; for (auto &v : G[u]) dfsg(v, rt); }

inline void solve() {
    ops.resize(0);
    io >> n;
    For (i, 1, n) a[i][0] = deg[i] = dep[i] = 0, pt[i].resize(0), es[i].resize(0), F[i].resize(0), G[i].resize(0);
    For (i, 1, n) io >> f[i];
    For (i, 1, n) io >> g[i];
    For (i, 1, n) {
        For (j, 1, n) vis[j] = 0;
        int j = i; while (!vis[j] && g[j] ^ j) vis[j] = 1, j = g[j];
        if (vis[j]) OVER;
    }
    For (i, 1, n) rtf[i] = f[i] == i, rtg[i] = g[i] == i, h[i] = f[i] != g[i], vis[i] = 0;
    For (i, 1, n) {
        int rt = i; while (!rtf[rt]) rt = f[rt];
        Rtf[i] = rt;
        rt = i; while (!rtg[rt]) rt = g[rt];
        Rtg[i] = rt;
    }
    For (i, 1, n) if (!rtf[i]) F[f[i]].pb(i);
    For (i, 1, n) if (!rtg[i]) G[g[i]].pb(i);
    For (i, 1, n) if (rtf[i]) dfs0(i);
    For (i, 1, n) if (h[i] && (!(h[f[i]] || dep[i] <= 2) || !rtf[g[i]])) OVER;
    For (i, 1, n) For (j, 1, n) visf[i][j] = visg[i][j] = 0;
    For (i, 1, n) dfsf(i, i), dfsg(i, i);
    For (i, 1, n) For (j, 1, n) if (i ^ j) {
        if (visf[i][j] && visg[j][i]) OVER;
        if (!visf[i][j] && visg[i][j] && !rtf[i]) OVER;
        if (!visf[i][j] && visg[Rtf[j]][i] && visg[i][j]) OVER;
    }
    For (i, 1, n) if (Rtg[i] ^ Rtg[Rtf[i]]) OVER;
    For (i, 1, n) if (h[i]) {
        pt[Rtf[i]].pb(i);
        if (g[i] ^ Rtf[i]) deg[Rtf[i]]++, es[g[i]].pb(Rtf[i]);
    }
    For (i, 1, n) if (rtg[i]) {
        queue<int > q; q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            //assert(!vis[u]);
            vis[u] = 1;
            a[i][++a[i][0]] = u;
            for (auto &v : es[u]) if (!--deg[v]) q.push(v);
        }
    }
    For (i, 1, n) if (rtf[i] && !vis[i]) OVER;
    puts("YES");
    For (i, 1, n) if (rtg[i]) {
        rFor (j, a[i][0], 1) {
            int u = a[i][j], v = a[i][j - 1];
            for (auto &x : pt[u]) ops.pb({x, 0});
            if (j > 1) {
                //assert(!rtg[u]);
                ops.pb({u, v});
                for (auto &x : pt[u]) if (g[x] ^ u) ops.pb({x, 0}), pt[v].pb(x);
            }
        }
    }
    printf("%d\n", (int)ops.size());
    for (auto &[x, y] : ops) if (!y) printf("1 %d\n", x); else printf("2 %d %d\n", x, y);
}

int main() {
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    io >> T;
    while (T--) solve();

    fclose(stdin); fclose(stdout);
    return 0;
}