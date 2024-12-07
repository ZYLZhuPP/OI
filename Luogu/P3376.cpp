#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 205, M = 1e4 + 5;
const ll INF = 1e18;

int n, m, s, t, u, v;
ll w;

namespace Dinic {
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll cap[M << 1];
    int lev[N], cur[N], gap[N], q[N], S, T;
    inline void add(int u, int v, ll f) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0;
    }
    bool bfs(int n) {
        memset(lev, 0, (n + 1) << 2); memcpy(cur, head, (n + 1) << 2);
        int h = 1, t = 0; lev[q[++t] = T] = 1;
        while (h <= t) {
            int u = q[h++], v;
            if (u == S) return 1;
            for (int i = head[u]; i; i = nxt[i]) if (cap[i ^ 1] && !lev[v = to[i]])
                lev[v] = lev[u] + 1, q[++t] = v;
        }
        return 0;
    }
    ll dfs(int u, ll r) {
        if (u == T) return r;
        ll flow = 0, f; int v;
        for (int &i = cur[u]; i; i = nxt[i]) if (cap[i] && lev[v = to[i]] == lev[u] - 1) {
            if (f = dfs(v, min(r - flow, cap[i]))) {
                cap[i] -= f, cap[i ^ 1] += f;
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

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> s >> t;
    while (m--) cin >> u >> v >> w, add(u, v ,w);
    cout << maxflow(n, s, t);

    return 0;
}
