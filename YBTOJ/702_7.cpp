#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef int ll;
const int N = 55;
const ll INF = 1e9;
int n, m, g[N][N], s, t, id[2][N][N], ans;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

namespace Dinic {
    const int N = 1e4 + 5, M = 4e4 + 5;
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll val[M << 1];
    int lev[N], cur[N], q[N], S, T;
    inline void add(int u, int v, ll w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; val[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; val[en] = 0;
    }
    bool bfs(int n) {
        memset(lev, 0, (n + 1) << 2); memcpy(cur, head, (n + 1) << 2);
        int h = 1, t = 0; lev[q[++t] = S] = 1;
        while (h <= t) {
            int u = q[h++], v;
            for (int i = head[u]; i; i = nxt[i]) if (val[i] > 0 && !lev[v = to[i]]) {
                lev[v] = lev[u] + 1; q[++t] = v;
                if (v == T) return 1;
            }
        }
        return 0;
    }
    ll dfs(int u, ll r) {
        if (u == T) return r;
        ll flow = 0, f; int v;
        for (int &i = cur[u]; i; i = nxt[i]) if (val[i] > 0 && lev[v = to[i]] == lev[u] + 1) {
            if (f = dfs(v, min(r - flow, val[i]))) {
                val[i] -= f, val[i ^ 1] += f;
                if ((flow += f) == r) break;
            }
        }
        if (flow < r) lev[u] = -1;
        return flow;
    }
    ll maxflow(int n, int s, int t) {
        S = s; T = t;
        ll res = 0;
        while (bfs(n)) res += dfs(s, INF);
        return res;
    }
}
using namespace Dinic;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, n) For (j, 1, m) cin >> g[i][j],
        id[0][i][j] = ((i - 1) * m + j) << 1, id[1][i][j] = id[0][i][j] | 1;
    s = n * m * 2 + 2, t = s + 1;
    For (i, 1, n) For (j, 1, m) {
        if (g[i][j] < 0) {
            int k = -1 - g[i][j], ma = 0;
            for (int x = i, y = j; x > 0 && x <= n && y > 0 && y <= m; x += dx[k], y += dy[k]) ma = max(ma, g[x][y]);
            ans += ma;
            int lx = i, ly = j;
            for (int x = i + dx[k], y = j + dy[k]; x > 0 && x <= n && y > 0 && y <= m; x += dx[k], y += dy[k]) {
                int w = ma - max(0, g[lx][ly]);
                if (k <= 1) add(id[0][lx][ly], id[0][x][y], w);
                else add(id[1][x][y], id[1][lx][ly], w);
                lx = x; ly = y;
                if (g[x][y] == ma) break;
            }
            if (k <= 1) add(s, id[0][i][j], INF);
            else add(id[1][i][j], t, INF);
        } else
            add(id[0][i][j], id[1][i][j], INF);
    }
    cout << ans - maxflow(t, s, t);

    return 0;
}
