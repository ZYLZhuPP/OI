#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, M = N * N, inf = 1e9;
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
    inline bool operator ~ () { return ~c; }
} io;

int n, H, W, id[N][N], tot, to[M][4], f[10][10][M], cnt[M << 2], q1[M], q2[M], ans;
const int dx[4] = {0, -1, 0, 1}, dy[4] = {1, 0, -1, 0};
bool vis[M][4], did[M];
char s[N][N];

inline int dfs(int x, int y, int k) {
    int o = id[x][y];
    if (vis[o][k]) return to[o][k];
    vis[o][k] = 1;
    int w = s[x][y]=='A'? (k+1)&3: s[x][y]=='C'? (k-1)&3: k;
    int a = x + dx[w], b = y + dy[w];
    return to[o][k] = id[a][b]? dfs(a, b, w): o;
}

int main() {
    memset(f, 63, sizeof f);
    io >> n >> W >> H;
    For (i, 1, H) {
        scanf("%s", s[i] + 1);
        For (j, 1, W) if (s[i][j] ^ 'x') {
            id[i][j] = ++tot;
            if (isdigit(s[i][j])) f[s[i][j]^48][s[i][j]^48][tot] = 0;
        }
    }
    For (i, 1, H) For (j, 1, W) if (id[i][j]) For (k, 0, 3) dfs(i, j, k);
    rFor (l, n, 1) For (r, l, n) {
        int *g = f[l][r];
        For (k, l, r - 1) For (i, 1, tot) cmin(g[i], f[l][k][i] + f[k + 1][r][i]);
        int mx = 0;
        For (i, 1, tot) if (g[i] < inf) cmax(mx, g[i]), ++cnt[g[i]];
        For (i, 1, mx) cnt[i] += cnt[i - 1];
        int  h1 = 1, t1 = cnt[mx], h2 = 1, t2 = 0;
        For (i, 1, tot) if (g[i] < inf) q1[cnt[g[i]]--] = i;
        while (h1 <= t1 || h2 <= t2) {
            int u = h1<=t1&&(h2>t2||g[q1[h1]]<g[q2[h2]])? q1[h1++]: q2[h2++];
            if (!did[u]) for (auto &v : to[u]) if (v && cmin(g[v], g[u] + 1)) q2[++t2] = v;
            did[u] = 1;
        }
        memset(cnt, 0, (mx + 1) << 2); memset(did, 0, tot + 1);
    }
    ans = inf;
    For (i, 1, tot) cmin(ans, f[1][n][i]);
    printf("%d", ans<inf? ans: -1);

    return 0;
}
