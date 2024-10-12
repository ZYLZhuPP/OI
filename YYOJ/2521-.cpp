#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, V = 1e6 + 5, M = 5e6 + 5, inf = 1e9;

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

int n, m, id[N][2][N], tot, a[N][N], b[N][N];
unordered_map<int, int > g[V];

namespace Dinic {
    int S, T, en = 1, nxt[M], to[M], cap[M], dep[V], head[V], cur[V], q[V], D;
    inline void add(int u, int v, const int &w) {
        nxt[++en] = head[u]; to[en] = v; cap[en] = w; head[u] = en;
        nxt[++en] = head[v]; to[en] = u; cap[en] = 0; head[v] = en;
    }
    inline bool bfs() {
        dep[T] = D + 2; memcpy(cur, head, (tot + 1) << 2);
        int h = 1, t = 0; q[++t] = T;
        while (h <= t) {
            int u = q[h++];
            for (int i = head[u], v; v = to[i], i; i = nxt[i]) if (cap[i ^ 1] && dep[v] <= D) {
                dep[v] = dep[u] + 1; q[++t] = v;
                if (v == S) return D = dep[v], 1;
            }
        }
        return 0;
    }
    inline int dfs(int u, const int &F) {
        if (u == T) return F;
        int f = 0;
        for (int &i = cur[u], v; v = to[i], i; i = nxt[i]) if (cap[i] && dep[v] == dep[u] - 1) {
            int x = dfs(v, min(cap[i], F - f));
            if (x) {
                cap[i] -= x; cap[i ^ 1] += x;
                f += x; if (F == f) return F;
            }
        }
        dep[u] = -1;
        return f;
    }
    inline int maxflow(int s, int t) {
        S = s; T = t;
        int res = 0, cnt = 0;
        while (bfs()) res += dfs(s, inf), cnt++;
        cerr << cnt << endl;
        return res;
    }
}
using namespace Dinic;

inline void Add(int u, int v, const int &w) {
    int x = ++tot, y = ++tot;
    add(v, x, w); add(u, x, w); add(y, u, w); add(x, y, w); add(y, v, w);
}

int main() {
    freopen("in.in", "r", stdin);
    io >> n >> m;
    For (i, 1, n) {
        For (j, 1, m - 1) io >> a[i][j] >> b[i][j];
        io >> a[i][m];
    }
    For (i, 1, m) id[1][0][i] = ++tot, id[n][1][i] = ++tot;
    For (i, 1, n - 1) {
        int x;
        io >> x;
        while (x--) {
            int l1, r1, l2, r2;
            io >> l1 >> r1 >> l2 >> r2;
            int x = ++tot;
            For (j, l1, r1) id[i][1][j] = x;
            For (j, l2, r2) id[i + 1][0][j] = x;
        }
    }
    For (i, 1, n) {
        For (j, 1, m) g[id[i][0][j]][id[i][1][j]] += a[i][j];
        For (j, 1, m - 1) g[id[i][0][j]][id[i][1][j + 1]] += b[i][j];
    }
    For (i, 1, tot) for (auto &[v, w] : g[i]) Add(i, v, w);
    int s = ++tot, t = ++tot;
    cerr << tot << " " << en << endl;
    For (i, 1, m) add(s, id[1][0][i], inf), add(id[n][1][i], t, inf);
    printf("%d", maxflow(s, t));

    return 0;
}
