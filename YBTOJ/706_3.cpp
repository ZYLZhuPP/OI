#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef int ll;
const ll INF = 1e9;

int n, m, s, t, x;
int f, fa, fb, a, b;

namespace SSP {
    const int N = 2e3 + 5, M = N << 2;
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll cap[M << 1], cost[M << 1];
    int cur[N], vis[N], S, T; ll dis[N], Cost;
    void add(int u, int v, ll f, ll w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f; cost[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0; cost[en] = -w;
    }
    bool SPFA(int n) {
        memset(dis, 31, sizeof dis); memset(vis, 0, sizeof vis);
        memcpy(cur, head, sizeof head);
        deque<int > q;
        q.push_back(T); dis[T] = 0; vis[T] = 1;
        while (!q.empty()) {
            int u = q.front(), v; q.pop_front(); vis[u] = 0;
            for (int i = head[u]; i; i = nxt[i])
                if (cap[i ^ 1] && dis[v = to[i]] > dis[u] + cost[i ^ 1]) {
                    dis[v] = dis[u] + cost[i ^ 1];
                    if (!vis[v]) vis[v] = 1, dis[v] < dis[q.empty()? 0: q.front()]?
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
    cin >> n >> a >> b >> f >> fa >> fb;
    s = n * 2 + 1, t = s + 1;
    For (i, 1, n) {
        add(s, i, INF, f);
        if (i + a + 1 <= n) add(n + i, i + a + 1, INF, fa);
        if (i + b + 1 <= n) add(n + i, i + b + 1, INF, fb);
        if (i < n) add(n + i, n + i + 1, INF, 0);
    }
    For (i, 1, n) cin >> x, add(s, n + i, x, 0), add(i, t, x, 0);
    Dinic(t, s, t, INF);
    cout << Cost;
    
    return 0;
}
