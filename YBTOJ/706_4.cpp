#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef int ll;
const int N = 45;
const ll INF = 1e9;

int n, s, t, ans, Case;
int f, c, o, a, b, si[N], sj[N];
char g[N][N];

namespace SSP {
    const int N = 105, M = N * N << 1;
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

void build(int x) {
    memset(head, 0, sizeof head); en = 1;
    For (i, 1, n) add(s, i, si[i], 0), add(i, n + i, x, 0), add(n + i, t, sj[i], 0);
    For (i, 1, n) For (j, 1, n) if (g[i][j] == '.') add(i, n + j, 1, 1);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n >> a >> b, n) {
        Case++;
        ans = -1; c = o = 0;
        memset(si, 0, sizeof si); memset(sj, 0, sizeof sj);
        For (i, 1, n) {
            cin >> (g[i] + 1);
            For (j, 1, n) {
                c += g[i][j] == 'C'; o += g[i][j] == '.';
                si[i] += g[i][j] != '/'; sj[j] += g[i][j] != '/';
            }
        }
        s = 2 * n + 1, t = s + 1;
        For (i, 0, n) {
            build(i);
            f = Dinic(t, s, t, INF);
            if (f == c + o && (c + o - Cost) * a >= i * b)
                ans = max(ans, o - Cost);
        }
        ~ans? cout << "Case " << Case << ": " << ans << endl
        : cout << "Case " << Case << ": impossible\n";
    }

    return 0;
}
