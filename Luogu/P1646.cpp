#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef int ll;
const int N = 1e4 + 5, M = 4e5 + 5;
const ll INF = 1e9;

int n, m, x, s, t, id[105][105];
ll ans;

namespace Dinic {
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll val[M << 1];
    int lev[N], cur[N], q[N], S, T, tim;
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
    For (i, 1, n) For (j, 1, m) id[i][j] = (i - 1) * m + j;
    s = n * m + 1; t = s + 1;
    For (i, 1, n) For (j, 1, m) {
        cin >> x; ans += x;
        add(s, id[i][j], x << 1);
    }
    For (i, 1, n) For (j, 1, m) {
        cin >> x; ans += x;
        add(id[i][j], t, x << 1);
    }
    For (i, 1, n - 1) For (j, 1, m) {
        cin >> x; ans += x;
        add(id[i][j], id[i + 1][j], x);
        add(id[i + 1][j], id[i][j], x);
        add(s, id[i][j], x), add(s, id[i + 1][j], x);
    }
    For (i, 1, n - 1) For (j, 1, m) {
        cin >> x; ans += x;
        add(id[i][j], id[i + 1][j], x);
        add(id[i + 1][j], id[i][j], x);
        add(id[i][j], t, x), add(id[i + 1][j], t, x);
    }
    For (i, 1, n) For (j, 1, m - 1) {
        cin >> x; ans += x;
        add(id[i][j], id[i][j + 1], x);
        add(id[i][j + 1], id[i][j], x);
        add(s, id[i][j], x), add(s, id[i][j + 1], x);
    }
    For (i, 1, n) For (j, 1, m - 1) {
        cin >> x; ans += x;
        add(id[i][j], id[i][j + 1], x);
        add(id[i][j + 1], id[i][j], x);
        add(id[i][j], t, x), add(id[i][j + 1], t, x);
    }
    cout << ans - (maxflow(t, s, t) >> 1);

    return 0;
}