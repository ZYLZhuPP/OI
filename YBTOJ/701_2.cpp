#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1005, M = 2e5 + 5, INF = 1e9;

int m, n, k, x, c[N], lst[N];

namespace Dinic {
    const int N = 105;
    int head[N], nxt[M << 1], to[M << 1], val[M << 1], en = 1;
    int lev[N], cur[N], q[N], S, T;
    void add(int u, int v, int w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; val[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; val[en] = 0;
    }
    bool bfs(int n) {
        For (i, 1, n) lev[i] = 0, cur[i] = head[i];
        int h = 1, t = 0; lev[q[++t] = S] = 1;
        while (h <= t) {
            int u = q[h++], v;
            for (int i = head[u]; i; i = nxt[i]) if (val[i] && !lev[v = to[i]]) {
                lev[v] = lev[u] + 1; q[++t] = v;
                if (v == T) return 1;
            }
        }
        return 0;
    }
    int dfs(int u, int r) {
        if (u == T || !r) return r;
        int flow = 0, f;
        for (int &i = cur[u]; i; i = nxt[i]) if (val[i]) {
            int v = to[i];
            if (lev[v] == lev[u] + 1 && (f = dfs(v, min(r - flow, val[i])))) {
                val[i] -= f; val[i ^ 1] += f;
                if ((flow += f) == r) break;
            }
        }
        if (flow < r) lev[u] = -1;
        return flow;
    }
    int maxflow(int n, int s, int t) {
        S = s; T = t;
        int res = 0;
        while (bfs(n)) res += dfs(S, INF);
        return res;
    }
}
using namespace Dinic;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> m >> n;
    For (i, 1, m) cin >> c[i];
    For (i, 1, n) {
        cin >> k;
        For (j, 1, k) {
            cin >> x;
            if (!lst[x]) add(1, i + 1, c[x]);
            else add(lst[x] + 1, i + 1, INF);
            lst[x] = i;
        }
        cin >> x;
        add(i + 1, n + 2, x);
    }
    cout << maxflow(n + 2, 1, n + 2);

    return 0;
}
