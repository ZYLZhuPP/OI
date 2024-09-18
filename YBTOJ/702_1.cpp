#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e3 + 5, M = 5e4 + 5;
const ll INF = 1e18;

int n, m, a, b, u, v, w, s, t;

namespace Dinic {
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll val[M << 1];
    int lev[N], cur[N], q[N], S, T, tim;
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
        while (bfs(n)) res += dfs(s, INF);
        return res;
    }
}
using namespace Dinic;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    s = n + 1, t = n + 2;
    For (i, 1, n) cin >> a >> b, add(s, i, a), add(i, t, b);
    For (i, 1, m) cin >> u >> v >> w, add(u, v, w), add(v, u, w);
    cout << maxflow(t, s, t);

    return 0;
}
