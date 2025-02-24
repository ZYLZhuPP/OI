#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 75, M = 1e6 + 5;
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

const int dx[3] = {1, 0, 0}, dy[3] = {0, 1, 0}, dz[3] = {0, 0, 1};
int n, m, id[N][N][N], tot, mn, mx, X[N], Y[N], Z[N], a[N][N][N], b[N][N][N], rt, vis[M], f[M], g[M];
vector<int > es[M], G[M], pt[N * 3];
basic_string<int > F[M], pre[M];

inline void dfs(int i, int s) {
    if (i > m) {
        cmin(mn, s); cmax(mx, s);
        return;
    }
    {
        int x = X[i], y = Y[i], z = Z[i], S = s;
        for (; x <= n; x++) if (!b[x][y][z]++) S += a[x][y][z];
        dfs(i + 1, S);
        for (x = X[i]; x <= n; x++) b[x][y][z]--;
    }
    {
        int x = X[i], y = Y[i], z = Z[i], S = s;
        for (; y <= n; y++) if (!b[x][y][z]++) S += a[x][y][z];
        dfs(i + 1, S);
        for (y = Y[i]; y <= n; y++) b[x][y][z]--;
    }
    {
        int x = X[i], y = Y[i], z = Z[i], S = s;
        for (; z <= n; z++) if (!b[x][y][z]++) S += a[x][y][z];
        dfs(i + 1, S);
        for (z = Z[i]; z <= n; z++) b[x][y][z]--;
    }
    {
        int x = X[i], y = Y[i], z = Z[i], S = s;
        for (; x > 0; x--) if (!b[x][y][z]++) S += a[x][y][z];
        dfs(i + 1, S);
        for (x = X[i]; x > 0; x--) b[x][y][z]--;
    }
    {
        int x = X[i], y = Y[i], z = Z[i], S = s;
        for (; y > 0; y--) if (!b[x][y][z]++) S += a[x][y][z];
        dfs(i + 1, S);
        for (y = Y[i]; y > 0; y--) b[x][y][z]--;
    }
    {
        int x = X[i], y = Y[i], z = Z[i], S = s;
        for (; z > 0; z--) if (!b[x][y][z]++) S += a[x][y][z];
        dfs(i + 1, S);
        for (z = Z[i]; z > 0; z--) b[x][y][z]--;
    }
}

int main() {
    freopen("glitter.in", "r", stdin);
    freopen("glitter.out", "w", stdout);
    io >> n;
    For (i, 1, n) For (j, 1, n) For (k, 1, n) id[i][j][k] = ++tot;
    For (i, 1, n) For (j, 1, n) For (k, 1, n) {
        pt[i + j + k].pb(id[i][j][k]);
        For (l, 0, 2) {
            int x = i + dx[l], y = j + dy[l], z = k + dz[l];
            if (max({x, y, z}) <= n) G[id[i][j][k]].pb(id[x][y][z]);
        }
    }
    int x;
    For (i, 1, n * n * n) {
        io >> f[i];
        while (io.c == ' ') io >> x, es[i].pb(x);
        if ((int)es[i].size() == 3) rt = i;
    }
    vis[g[1] = rt] = 1;
    For (i, 0, 2) vis[g[G[1][i]] = es[rt][i]] = 1;
    For (i, 4, 3 * n - 1) {
        map<basic_string<int >, int > mp;
        for (auto &u : pt[i]) {
            for (auto &v : G[u]) F[v] += u;
            for (auto &v : es[g[u]]) if (!vis[v]) pre[v] += u;
        }
        for (auto &u : pt[i]) for (auto &v : es[g[u]]) sort(pre[v].begin(), pre[v].end()), mp[pre[v]] = v;
        for (auto &u : pt[i + 1]) sort(F[u].begin(), F[u].end()), g[u] = mp[F[u]];
    }
    For (i, 1, n) For (j, 1, n) For (k, 1, n) {
        int u = g[id[i][j][k]];
        if (!f[u]) X[++m] = i, Y[m] = j, Z[m] = k;
        a[i][j][k] = f[u];
    }
    mn = 1e9, mx = 0;
    dfs(1, 0);
    printf("%d %d", mn, mx);

    fclose(stdin); fclose(stdout);
    return 0;
}
