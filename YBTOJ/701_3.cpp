#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 45, M = N * N * 4;
const ll INF = 1e18;

int Q, n, m, B, W, t, g[N][N];
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
ll a[N][N], b, w;

namespace Dinic {
    const int N = 2e3 + 5;
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll val[M << 1];
    int lev[N], cur[N], q[N], S, T;
    void add(int u, int v, ll w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; val[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; val[en] = 0;
    }
    bool bfs(int n) {
        For (i, 1, n) lev[i] = 0, cur[i] = head[i];
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
        if (u == T || !r) return r;
        ll flow = 0, f;
        for (int &i = cur[u]; i; i = nxt[i]) if (val[i] > 0) {
            int v = to[i];
            if (lev[v] == lev[u] + 1 && (f = dfs(v, min(r - flow, val[i])))) {
                val[i] -= f; val[i ^ 1] += f;
                if ((flow += f) == r) break;
            }
        }
        if (flow < r) lev[u] = -1;
        return flow;
    }
    ll maxflow(int n, int s, int t) {
        S = s; T = t;
        ll res = 0;
        while (bfs(n)) res += dfs(S, INF);
        return res;
    }
}
using namespace Dinic;

bool ok(ll x) {
    en = 1;
    memset(head, 0, sizeof head);
    For (i, 1, n) For (j, 1, m) {
        int u = g[i][j];
        if ((i + j) & 1) {
            add(1, u, x - a[i][j]);
            For (k, 0, 3) {
                int x = i + dx[k], y = j + dy[k];
                if (x > 0 && x <= n && y > 0 && y <= m)
                    add(u, g[x][y], INF);
            }
        } else add(u, t, x - a[i][j]);
    }
    return maxflow(t, 1, t) == x * B - b;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> Q;
    while (Q--) {
        B = W = b = w = 0;
        ll l = 0, r = INF;
        cin >> n >> m;
        For (i, 1, n) For (j, 1, m) {
            g[i][j] = (i - 1) * m + j + 1;
            cin >> a[i][j]; l = max(l, a[i][j]);
            if ((i + j) & 1) B++, b += a[i][j];
            else W++, w += a[i][j];
        }
        t = n * m + 2;
        if (W > B && w - b >= l) {
            ll x = w - b;
            if (ok(x)) cout << x * B - b << endl;
            else cout << -1 << endl;
        } else {
            ll ans = -1;
            while (l <= r) {
                ll m = (l + r) >> 1;
                if (ok(m)) ans = m, r = m - 1;
                else l = m + 1;
            }
            cout << ans * B - b << endl;
        }
    }

    return 0;
}
