#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 2e3 + 5, M = 1e5 + 5;
const lf inf = 1e9, eps = 1e-7;

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

int n, m, a[M], b[M], s, t, ans;

namespace Dinic {
    int head[N], nxt[M << 1], to[M << 1], en = 1; lf cap[M << 1];
    int lev[N], cur[N], q[N], S, T;
    inline void add(int u, int v, lf w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0;
    }
    bool bfs(int n) {
        For (i, 1, n) lev[i] = 0, cur[i] = head[i];
        int h = 1, t = 0; lev[q[++t] = S] = 1;
        while (h <= t) {
            int u = q[h++], v;
            for (int i = head[u]; i; i = nxt[i]) if (cap[i] > eps && !lev[v = to[i]]) {
                lev[v] = lev[u] + 1; q[++t] = v;
                if (v == T) return 1;
            }
        }
        return 0;
    }
    lf dfs(int u, lf r) {
        if (u == T) return r;
        lf flow = 0;
        for (int &i = cur[u]; i; i = nxt[i]) if (cap[i] > eps && lev[to[i]] == lev[u] + 1) {
            lf f = dfs(to[i], min(r - flow, cap[i]));
            if (f <= eps) continue;
            cap[i] -= f, cap[i ^ 1] += f; flow += f;
            if (r - flow <= eps) break;
        }
        if (r - flow > eps) lev[u] = 0;
        return flow;
    }
    lf maxflow(int n, int s, int t) {
        S = s; T = t;
        lf res = 0;
        while (bfs(n)) res += dfs(s, inf);
        return res;
    }
}
using namespace Dinic;

bool ok(lf k) {
    en = 1;
    For (i, 1, t) head[i] = 0;
    For (i, 1, n) add(i, t, k);
    For (i, 1, m) add(s, i + n, 1);
    For (i, 1, m) add(i + n, a[i], inf), add(i + n, b[i], inf);
    return m - Dinic::maxflow(t, s, t) > eps;
}

int main() {
    while (~(io >> n >> m)) {
        if (!m) { puts("1\n1\n"); continue; }
        For (i, 1, m) io >> a[i] >> b[i];
        s = n + m + 1, t = s + 1;

        lf l = 0, r = m;
        while (r - l > eps) {
            lf m = (l + r) / 2;
            if (ok(m)) l = m;
            else r = m;
        }
        ok(l);
        ans = 0;
        For (i, 1, t) lev[i] = 0;
        int h = 1, t = 0; lev[q[++t] = S] = 1;
        while (h <= t) {
            int u = q[h++], v;
            if (u <= n) ans++;
            for (int i = head[u]; i; i = nxt[i]) if (cap[i] && !lev[v = to[i]]) {
                lev[v] = lev[u] + 1; q[++t] = v;
            }
        }
        printf("%d\n", ans);
        For (i, 1, n) if (lev[i]) printf("%d\n", i);
        puts("");
    }

    return 0;
}
