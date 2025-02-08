#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e3 + 5, M = 5e4 + 5;
const ll INF = 1e18;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

int n, m, s, t, u, v;
ll f, w;

namespace SSP {
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll cap[M << 1], cost[M << 1];
    int cur[N], inq[N], vis[N], S, T; ll dis[N], Cost;
    inline void add(int u, int v, ll f, ll w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f; cost[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0; cost[en] = -w;
    }
    inline bool SPFA(int n) {
        For (i, 1, n) dis[i] = INF, inq[i] = vis[i] = 0, cur[i] = head[i];
        queue<int > q;
        dis[T] = 0; q.push(T); inq[T] = 1;
        while (!q.empty()) {
            int u = q.front(), v; q.pop(); inq[u] = 0;
            for (int i = head[u]; i; i = nxt[i]) if (cap[i ^ 1])
                if (cmin(dis[v = to[i]], dis[u] + cost[i ^ 1]) && !inq[v]) q.push(v), inq[v] = 1;
        }
        return dis[S] < INF;
    }
    inline ll dfs(int u, ll r) {
        if (u == T) return Cost += dis[S] * r, r;
        vis[u] = 1;
        ll flow = 0, f; int v;
        for (int &i = cur[u]; i; i = nxt[i])
            if (!vis[v = to[i]] && cap[i] && dis[v] == dis[u] - cost[i]) {
                f = dfs(v, min(r - flow, cap[i]));
                if (f) {
                    cap[i] -= f; cap[i ^ 1] += f;
                    if ((flow += f) == r) break;
                }
            }
        if (flow == r) vis[u] = 0;
        return flow;
    }
    inline ll Dinic(int n, int s, int t, ll lim) {
        S = s, T = t, Cost = 0;
        ll res = 0;
        while (res < lim && SPFA(n)) res += dfs(S, lim - res);
        return res;
    }
}
using namespace SSP;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> s >> t;
    For (i, 1, m) cin >> u >> v >> f >> w, add(u, v, f, w);
    cout << Dinic(n, s, t, INF) << " " << Cost;

    return 0;
}
