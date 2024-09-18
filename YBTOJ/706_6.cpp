#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 205;
const ll INF = 1e18;

int n, s, t, a[N], b[N], c[N], d[N];
bool flag = 1;

namespace SSP {
    const int M = N * N << 1;
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll cap[M << 1], cost[M << 1];
    int cur[N], vis[N], S, T; ll dis[N], Cost;
    void add(int u, int v, ll f, ll w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f; cost[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0; cost[en] = -w;
    }
    bool SPFA(int n) {
        memset(dis, -31, sizeof dis); memset(vis, 0, sizeof vis);
        memcpy(cur, head, sizeof head);
        deque<int > q;
        q.push_back(T); dis[T] = 0; vis[T] = 1;
        while (!q.empty()) {
            int u = q.front(), v; q.pop_front(); vis[u] = 0;
            for (int i = head[u]; i; i = nxt[i])
                if (cap[i ^ 1] && dis[v = to[i]] < dis[u] + cost[i ^ 1]) {
                    dis[v] = dis[u] + cost[i ^ 1];
                    if (!vis[v]) vis[v] = 1, dis[v] > dis[q.empty()? 0: q.front()]?
                        q.push_front(v): q.push_back(v);
                }
        }
        return dis[S] > dis[0];
    }
    ll dfs(int u, ll r) {
        if (u == T) {
            if (Cost + r * dis[S] >= 0) return Cost += r * dis[S], r;
            else return flag = 0, Cost / (-dis[S]);
        }
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
        while (flag && res < lim && SPFA(n)) res += dfs(S, lim - res);
        return res;
    }
}
using namespace SSP;

int getcnt(int x) {
    int res = 0, sq = sqrt(x);
    For (i, 2, sq) while (!(x % i)) res++, x /= i;
    return res + (x > 1);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    s = n + 1, t = s + 1;
    For (i, 1, n) cin >> a[i];
    For (i, 1, n) cin >> b[i];
    For (i, 1, n) cin >> c[i];
    For (i, 1, n) {
        d[i] = getcnt(a[i]);
        if (d[i] & 1) add(s, i, b[i], 0);
        else add(i, t, b[i], 0);
    }
    For (i, 1, n) if (d[i] & 1)
        For (j, 1, n) if ((d[i] == d[j] + 1 && !(a[i] % a[j])) || (d[j] == d[i] + 1 && !(a[j] % a[i])))
            add(i, j, INF, 1ll * c[i] * c[j]);
    cout << Dinic(t, s, t, INF);

    return 0;
}
