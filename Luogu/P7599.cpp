#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e5 + 5, inf = 1e9;

int h[N], f[2][N][20], g[N][20], vis[N];

void dfs(int u) {
    if (u == -1 || vis[u]) return;
    vis[u] = 1;
    int v0 = f[0][u][0], v1 = f[1][u][0];
    g[u][0] = ~v0&&~v1? h[v0]>h[v1]? v0: v1: v0|v1;
    dfs(g[u][0]);
    For (i, 1, 19) if (~g[u][i - 1]) g[u][i] = g[g[u][i - 1]][i - 1]; else break;
}

void init(int n, vector<int > H) {
    For (i, 0, n - 1) h[i] = H[i];
    memset(f, -1, sizeof f);
    int q[n + 1], t = 0;
    For (i, 0, n - 1) {
        while (t && h[q[t]] < h[i]) f[1][q[t--]][0] = i;
        if (t) f[0][i][0] = q[t];
        q[++t] = i;
    }
    memset(g, -1, sizeof g);
    For (i, 0, n - 1) if (!vis[i]) dfs(i);
    For (i, 0, n - 1) For (j, 1, 19)
        if (~f[0][i][j - 1]) f[0][i][j] = f[0][f[0][i][j - 1]][j - 1]; else break;
    rFor (i, n - 1, 0) For (j, 1, 19)
        if (~f[1][i][j - 1]) f[1][i][j] = f[1][f[1][i][j - 1]][j - 1]; else break;
}

int getmx(int l, int r, int k, int mx = inf) {
    int u = k? l: r;
    rFor (i, 19, 0) {
        int v = f[k][u][i];
        if (l <= v && v <= r && h[v] < mx) u = v;
    }
    return u;
}

int minimum_jumps(int A, int B, int C, int D) {
    int mBC = h[getmx(B, C - 1, 1)], mCD = h[getmx(C, D, 1)];
    if (mCD < mBC) return -1;
    B = getmx(A, B, 0, mCD);
    if (h[B] >= mBC) return 1;
    int res = 0;
    rFor (i, 19, 0) if (~g[B][i] && h[g[B][i]] < mBC) B = g[B][i], res |= 1 << i;
    if (~g[B][0] && h[g[B][0]] < mCD) B = g[B][0], res++;
    rFor (i, 19, 0) if (~f[1][B][i] && f[1][B][i] < C) B = f[1][B][i], res += 1 << i;

    return res + 1;
}
