#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 1e5 + 5;
const lf inf = 1e18;

struct P { int id; lf dis; bool operator < (const P &a) const { return dis > a.dis; } };
struct Edge { int to, w; };
vector<Edge > es1[N], es2[N];
vector<int > kd;

int n, m, K, T;
char vis[N];
lf ans, _[2][N], *f = _[0], *g = _[1];

inline void mem(lf a[]) { For (i, 0, n - 1) a[i] = inf; }
inline void mem(char a[]) { memset(a, 0, n); }

void dfs(int u) {
    if (u == T) return void(ans = inf);
    vis[u] = 1;
    if (kd[u] == 0) g[u] = 0;
    for (auto &[v, w] : es1[u]) if (!vis[v]) dfs(v);
}

lf solve(int _n, int _m, int _K, int _T, vector<int > x, vector<int > y, vector<int > c, vector<int > arr) {
    n = _n, m = _m, K = min(_K, 68), T = _T, kd = arr;
    For (i, 0, n - 1) es1[i].resize(0), es2[i].resize(0);
    For (i, 0, m - 1) {
        int u = x[i], v = y[i], w = c[i];
        if (u ^ T) {
            es1[u].pb({v, w});
            if (kd[v] == 2) es2[u].pb({v, w});
        }
        if (v ^ T) {
            es1[v].pb({u, w});
            if (kd[u] == 2) es2[v].pb({u, w});
        }
    }
    ans = -1;
    mem(g); mem(vis);
    g[0] = 0;
    dfs(0);
    if (ans == -1) return -1;

    For (o, 0, K) {
        swap(f, g);
        mem(g); mem(vis);
        priority_queue<P > q;
        For (i, 0, n - 1) if (f[i] < inf) q.push({i, f[i]});
        while (!q.empty()) {
            int u = q.top().id; q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto &[v, w] : es1[u]) if (!vis[v] && f[v] > f[u] + w) {
                f[v] = f[u] + w;
                q.push({v, f[v]});
            }
            for (auto &[v, w] : es2[u]) g[v] = min(g[v], (f[u] + w) / 2);
        }
        ans = min(ans, f[T]);
    }

    return ans;
}
