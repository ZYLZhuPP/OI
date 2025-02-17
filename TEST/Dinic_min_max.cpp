#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5, M = 2e5 + 5, inf = 1e9;

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

namespace Dinic {
    int head[N], nxt[M << 1], to[M << 1], en = 1, cap[M << 1];
    int lev[N], cur[N], q[N], S, T;
    inline void add(int u, int v, int f) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0;
    }
    inline bool bfs(int n) {
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
    inline int dfs(int u, int r) {
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
    inline int maxflow(int n, int s, int t) {
        S = s; T = t;
        int res = 0;
        while (bfs(n)) res += dfs(S, inf);
        return res;
    }
}
using namespace Dinic;

int deg[N], sum;
inline void add(int u, int v, int l, int r) {
    deg[u] -= l; deg[v] += l;
    add(u, v, r - l);
}

int solve() {
    en = 1; sum = 0;
    memset(deg, 0, sizeof deg);
    memset(head, 0, sizeof head);
    int x, y, z, l, r;
    int S0 = n + m + 1, T0 = S0 + 1;
    For (i, 1, m) io >> x, add(n + i, T0, x, inf);
    For (i, 1, n) {
        io >> x >> y;
        add(S0, i, 0, y);
        while (x--) io >> z >> l >> r, z++, add(i, n + z, l, r);
    }
    int S1 = T0 + 1, T1 = S1 + 1;
    For (i, 1, T0) if (deg[i] > 0) add(S1, i, deg[i]), sum += deg[i]; else if (deg[i] < 0) add(i, T1, -deg[i]);
    add(T0, S0, 0, inf);
    if (maxflow(T1, S1, T1) ^ sum) return -1;
    return maxflow(T0, S0, T0);
}

int main() {
    while (~(io >> n >> m)) printf("%d\n", solve());

    return 0;
}
