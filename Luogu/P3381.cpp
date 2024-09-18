#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef int ll;
const int N = 5e3 + 5, M = 5e4 + 5;
const ll INF = 1e9;

int n, m, s, t, u, v;
ll f, w;

namespace SSP {
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll cap[M << 1], cost[M << 1];
    int dis[N], cur[N], vis[N], S, T; ll Cost;
    void add(int u, int v, ll f, ll w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f; cost[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0; cost[en] = -w;
    }
    bool SPFA(int n) {
        memset(dis, 31, (n + 1) << 2); memset(vis, 0, (n + 1) << 2);
        memcpy(cur, head, (n + 1) << 2);
        deque<int > q;
        q.push_back(T); dis[T] = 0; vis[T] = 1;
        while (!q.empty()) {
            int u = q.front(), v; q.pop_front(); vis[u] = 0;
            for (int i = head[u]; i; i = nxt[i])
                if (cap[i ^ 1] && dis[v = to[i]] > dis[u] + cost[i ^ 1]) {
                    dis[v] = dis[u] + cost[i ^ 1];
                    if (!vis[v]) vis[v] = 1, dis[v] < dis[q.front()]?
                        q.push_front(v): q.push_back(v);
                }
        }
        return dis[S] < dis[0];
    }
    ll dfs(int u, ll r) {
        if (u == T) return Cost += dis[S] * r, r;
        vis[u] = 1;
        ll flow = 0, f; int v;
        for (int &i = cur[u]; i; i = nxt[i])
            if (!vis[v = to[i]] && cap[i] && dis[u] == dis[v] + cost[i]) {
                f = dfs(v, min(r - flow, cap[i]));
                if (f) {
                    cap[i] -= f; cap[i ^ 1] += f;
                    if ((flow += f) == r) break;
                }
            }
        if (flow == r) vis[u] = 0;
        return flow;
    }
    ll Dinic(int n, int s, int t, ll lim) {
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
