#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef int ll;
const int N = 105, M = N * N;
const ll INF = 1e9;
int n, m, x, s, t, ans;
char st[N * N];

namespace Dinic {
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll val[M << 1];
    int lev[N], cur[N], q[N], S, T, tim;
    inline void add(int u, int v, ll w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; val[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; val[en] = 0;
    }
    bool bfs(int n) {
        memset(lev, 0, (n + 1) << 2); memcpy(cur, head, (n + 1) << 2);
        int h = 1, t = 0; lev[q[++t] = S] = 1;
        while (h <= t) {
            int u = q[h++], v;
            for (int i = head[u]; i; i = nxt[i]) if (val[i] > 0 && !lev[v = to[i]]) {
                lev[v] = lev[u] + 1; q[++t] = v;
                if (v == T) return 1;
            }
        }
        return 0;
    }
    ll dfs(int u, ll r) {
        if (u == T) return r;
        ll flow = 0, f; int v;
        for (int &i = cur[u]; i; i = nxt[i]) if (val[i] > 0 && lev[v = to[i]] == lev[u] + 1) {
            if (f = dfs(v, min(r - flow, val[i]))) {
                val[i] -= f, val[i ^ 1] += f;
                if ((flow += f) == r) break;
            }
        }
        if (flow < r) lev[u] = -1;
        return flow;
    }
    ll maxflow(int n, int s, int t) {
        S = s; T = t;
        ll res = 0;
        while (bfs(n)) res += dfs(s, INF);
        return res;
    }
}
using namespace Dinic;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    s = n + m + 1; t = s + 1;
    For (i, 1, n) {
        cin >> x; ans += x; add(s, i, x);
        cin.getline(st, N * N); int l = strlen(st); st[l] = ' ';
        x = 0;
        For (j, 1, l) {
            if (isdigit(st[j])) x = (x << 3) + (x << 1) + (st[j] ^ 48);
            else {
                add(i, x + n, INF);
                x = 0;
            }
        }
    }
    For (i, 1, m) cin >> x, add(i + n, t, x);
    ans -= maxflow(t, s, t);
    For (i, 1, n) if (lev[i]) cout << i << " ";
    cout << endl;
    For (i, 1, m) if (lev[i + n]) cout << i << " ";
    cout << endl;
    cout << ans;

    return 0;
}
