#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 205, M = 2e4 + 5, inf = 1e7;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m;
int inq[N], dis[N], vis[N];
vector<pair<int, int > > es[N];

namespace Dinic {
    int head[N], nxt[M << 1], to[M << 1], en = 1, cap[M << 1];
    int lev[N], cur[N], q[N], S, T;
    inline void add(int u, int v, int f) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0;
    }
    bool bfs(int n) {
        memset(lev, 0, (n + 1) << 2); memcpy(cur, head, (n + 1) << 2);
        int h = 1, t = 0; lev[q[++t] = T] = 1;
        while (h <= t) {
            int u = q[h++], v;
            for (int i = head[u]; i; i = nxt[i]) if (cap[i ^ 1] && !lev[v = to[i]]) {
                lev[v] = lev[u] + 1; q[++t] = v;
                if (v == S) return 1;
            }
        }
        return 0;
    }
    int dfs(int u, int r) {
        if (u == T) return r;
        int flow = 0, f, v;
        for (int &i = cur[u]; i; i = nxt[i]) if (cap[i] && lev[v = to[i]] == lev[u] - 1) {
            f = dfs(v, min(r - flow, cap[i]));
            if (f) {
                cap[i] -= f, cap[i ^ 1] += f;
                if ((flow += f) == r) break;
            }
        }
        if (flow < r) lev[u] = -1;
        return flow;
    }
    int maxflow(int n, int s, int t) {
        S = s; T = t;
        int res = 0;
        while (bfs(n)) res += dfs(S, inf);
        return res;
    }
}
using namespace Dinic;

inline void SPFA(int rt) {
    queue<int > q;
    For (i, 1, n) dis[i] = inf;
    dis[rt] = 0, q.push(rt), inq[rt] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for (auto &[v, w] : es[u]) if (cmin(dis[v], dis[u] + w) && !inq[v]) q.push(v), inq[v] = 1;
    }
}

int main() {
    io >> n >> m;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, u++, v++, es[u].pb({v, w}), es[v].pb({u, w});
    SPFA(1);
    For (u, 1, n) {
        add(u, u + n, 1);
        for (auto &[v, w] : es[u]) if (dis[v] == dis[u] + w) {
            if (u == 1 && v == n) { puts("IMPOSSIBLE"); return 0; }
            add(u + n, v, inf);
        }
    }
    printf("%d", maxflow(n + n, 1 + n, n));

    return 0;
}
