#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 205;

int n, m, s, t, x[N], y[N], b[N], p[N], q[N], c[N], d1[N], d2[N];
int g[N][N], dis[N], vis[N], e[N][N];
bool flag;

int dfs(int u) {
    vis[u] = 1;
    For (v, 1, t) if (dis[v] > dis[u] + g[u][v]) {
        if (vis[v]) {
            if (u <= n) e[u][v - n]++;
            else e[v][u - n]--;
            flag = 1;
            return v;
        }
        dis[v] = dis[u] + g[u][v];
        int r = dfs(v);
        if (flag) {
            if (!r) return 0;
            if (u <= n) e[u][v - n]++;
            else e[v][u - n]--;
            return r == u? 0: r;
        }
    }
    vis[u] = 0;
    return 0;
}

inline int dist(int i, int j) { return abs(x[i] - p[j]) + abs(y[i] - q[j]) + 1; }

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    s = n + m + 1, t = s + 1;
    For (i, 1, n) cin >> x[i] >> y[i] >> b[i];
    For (i, 1, m) cin >> p[i] >> q[i] >> c[i];
    memset(g, 31, sizeof g);
    For (i, 1, n) For (j, 1, m) {
        int x; cin >> x; e[i][j] = x;
        g[i][j + n] = dist(i, j);
        if (x) d1[i] += x, d2[j] += x, g[j + n][i] = -dist(i, j);
    }
    For (i, 1, n) {
        if (d1[i] < b[i]) g[s][i] = 0;
        if (d1[i]) g[i][s] = 0;
    }
    For (i, 1, m) {
        if (d2[i] < c[i]) g[i + n][t] = 0;
        if (d2[i]) g[t][i + n] = 0;
    }
    memset(dis, 31, sizeof dis); dis[t] = 0;
    dfs(t);
    if (flag) {
        cout << "SUBOPTIMAL\n";
        For (i, 1, n) For (j, 1, m) cout << e[i][j] << (j<m? " ": i<n? "\n": "");
    } else cout << "OPTIMAL";

    return 0;
}
