#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 4e5 + 5;

int n;
bool vis[N];
ll dis[N], dx[N], dy[N];
vector<array<int, 2 > > es[N];

inline void dfs(int u, int pre, ll d, ll dis[]) {
    dis[u] = d;
    for (auto &[v, w] : es[u]) if (v ^ pre) dfs(v, u, d + w, dis);
}

inline int solve(ll K) {
    int cnt = 0;
    priority_queue<pair<ll, int > > q1, q2;
    For (i, 0, n - 1) q1.push({-dx[i], i}), dx[i + n] = dy[i] - dx[i], q2.push({-dy[i], i}), vis[i] = vis[i + n] = 0;
    while (K >= -q1.top().st) {
        int x = q1.top().nd; q1.pop(); while (!q1.empty() && vis[q1.top().nd]) q1.pop();
        if (!q1.empty() && !q2.empty() && -q2.top().st <= K && dx[x] - q1.top().st >= -q2.top().st) q1.push({-dx[x], x}), x = q2.top().nd, q2.pop();
        if (x < n) q1.push({-dx[x + n], x + n});
        K -= dx[x]; vis[x] = 1; cnt++;
        while (!q1.empty() && vis[q1.top().nd]) q1.pop();
        while (!q2.empty() && vis[q2.top().nd]) q2.pop();
    }
    return cnt;
}

int max_score(int m, int X, int Y, ll K, vector<int > U, vector<int > V, vector<int > W) {
    int ans1 = 0, ans2 = 0;
    n = m;
    For (i, 0, n - 1) vector<array<int, 2 > >().swap(es[i]);
    For (i, 0, n - 2) es[U[i]].pb({V[i], W[i]}), es[V[i]].pb({U[i], W[i]});
    dfs(X, -1, 0, dx); dfs(Y, -1, 0, dy);
    ll D = dx[Y];
    For (i, 0, n - 1) {
        if (dx[i] > dy[i]) swap(dx[i], dy[i]);
        dis[i] = dx[i], dis[i + n] = dy[i];
    }
    sort(dis, dis + 2 * n);
    ll s = K;
    For (i, 0, 2 * n - 1) if (s >= dis[i]) ans1++, s -= dis[i]; else break;
    For (i, 0, n - 1) if (dx[i] + dy[i] == D) K -= dx[i], ans2++, dx[i] = dy[i] - dx[i], dy[i] = K + 1;
    if (K < 0) return ans1;
    ans2 += solve(K);
    return max(ans1, ans2);
}