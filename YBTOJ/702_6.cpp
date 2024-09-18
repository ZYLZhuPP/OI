#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef int ll;
const int N = 105;
const ll INF = 1e9;
int n, m, x, s, t, id[N][N], ans;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

namespace Dinic {
    const int N = 3e4 + 5, M = 3e5 + 5;
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
    s = n * m * 3 + 1, t = s + 1;
    For (i, 1, n) For (j, 1, m) {
        id[i][j] = (i - 1) * m + j;
        cin >> x; ans += x; add(s, id[i][j], x);
    }
    For (i, 1, n) For (j, 1, m) cin >> x, ans += x, add(id[i][j], t, x);
    For (i, 1, n) For (j, 1, m) {
        int p = n * m + id[i][j];
        cin >> x; ans += x; add(s, p, x); add(p, id[i][j], INF);
        For (k, 0, 3) {
            int x = i + dx[k], y = j + dy[k];
            if (x > 0 && x <= n && y > 0 && y <= m) add(p, id[x][y], INF);
        }
    }
    For (i, 1, n) For (j, 1, m) {
        int p = n * m * 2 + id[i][j];
        cin >> x; ans += x; add(p, t, x); add(id[i][j], p, INF);
        For (k, 0, 3) {
            int x = i + dx[k], y = j + dy[k];
            if (x > 0 && x <= n && y > 0 && y <= m) add(id[x][y], p, INF);
        }
    }
    cout << ans - maxflow(t, s, t);

    return 0;
}
