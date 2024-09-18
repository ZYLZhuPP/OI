#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 55, M = N * N, INF = 1e9;

int n, a1, a2, b1, b2, x, y, v1, v2, g[N][N];
char s[N];

namespace Dinic {
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
    while (cin >> n >> a1 >> a2 >> x >> b1 >> b2 >> y) {
        a1 += 2; a2 += 2; b1 += 2; b2 += 2;
        x *= 2; y *= 2;
        For (i, 0, n - 1) {
            cin >> s;
            For (j, 0, n - 1) g[i][j] = s[j]=='O'? 2: s[j]=='N'? INF: 0;
        }
        en = 1;
        memset(head, 0, sizeof head);
        add(1, a1, x); add(1, b1, y);
        add(a2, n + 2, x); add(b2, n + 2, y);
        For (i, 0, n - 1) For (j, 0, n - 1) add(i + 2, j + 2, g[i][j]);
        v1 = maxflow(n + 2, 1, n + 2);
        en = 1;
        memset(head, 0, sizeof head);
        add(1, a1, x); add(1, b2, y);
        add(a2, n + 2, x); add(b1, n + 2, y);
        For (i, 0, n - 1) For (j, 0, n - 1) add(i + 2, j + 2, g[i][j]);
        v2 = maxflow(n + 2, 1, n + 2);
        cout << ((v1 == x + y && v2 == x + y)? "Yes": "No") << endl;
    }

    return 0;
}
