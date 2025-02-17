#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 605, M = 2e3 + 5;
const int INF = 1e9;
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

namespace SSP {
    int head[N], nxt[M << 1], to[M << 1], en = 1; int cap[M << 1], cost[M << 1];
    int cur[N], inq[N], vis[N], S, T; int dis[N], Cost;
    inline void add(int u, int v, int f, int w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f; cost[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0; cost[en] = -w;
    }
    inline bool SPFA(int n) {
        For (i, 1, n) dis[i] = INF, inq[i] = vis[i] = 0, cur[i] = head[i];
        queue<int > q;
        dis[T] = 0; q.push(T); inq[T] = 1;
        while (!q.empty()) {
            int u = q.front(), v; q.pop(); inq[u] = 0;
            for (int i = head[u]; i; i = nxt[i]) if (cap[i ^ 1])
                if (cmin(dis[v = to[i]], dis[u] + cost[i ^ 1]) && !inq[v]) q.push(v), inq[v] = 1;
        }
        return dis[S] < INF;
    }
    inline int dfs(int u, int r) {
        if (u == T) return Cost += dis[S] * r, r;
        vis[u] = 1;
        int flow = 0, f; int v;
        for (int &i = cur[u]; i; i = nxt[i])
            if (!vis[v = to[i]] && cap[i] && dis[v] == dis[u] - cost[i]) {
                f = dfs(v, min(r - flow, cap[i]));
                if (f) {
                    cap[i] -= f; cap[i ^ 1] += f;
                    if ((flow += f) == r) break;
                }
            }
        if (flow == r) vis[u] = 0;
        return flow;
    }
    inline int Dinic(int n, int s, int t, int lim) {
        S = s, T = t, Cost = 0;
        int res = 0;
        while (res < lim && SPFA(n)) res += dfs(S, lim - res);
        return res;
    }
}
using namespace SSP;

int T, n, A, B, tot, a[N], b[N], x[N], s[N], t[N];
double P;

inline void get(int &x) { x = lower_bound(a + 1, a + tot + 1, x) - a; }

inline void solve() {
    memset(b, 0, sizeof b);
    memset(head, 0, sizeof head); en = 1;
    io >> n >> A >> B;
    scanf("%lf", &P);
    tot = 0;
    For (i, 1, n) io >> x[i] >> s[i] >> t[i], a[++tot] = s[i], a[++tot] = t[i];
    sort(a + 1, a + tot + 1); tot = unique(a + 1, a + tot + 1) - a - 1;
    For (i, 1, n) get(s[i]), get(t[i]), b[s[i]]++, b[t[i]]--;
    For (i, 1, tot) if ((b[i] += b[i - 1]) > A + B) { puts("impossible"); return; }
    int S = n + tot + 1, T = S + 1;
    For (i, 1, tot - 1) add(i, i + 1, A, 0);
    For (i, 1, n) add(S, s[i], 1, 0), add(s[i], tot + i, 1, x[i]), add(s[i] + 1, tot + i, 1, floor(P * x[i] + 1e-5)), add(t[i], tot + i, 1, 0), add(tot + i, T, 1, 0);
    Dinic(T, S, T, INF);
    printf("%d\n", Cost);
}

int main() {
    freopen("airport.in", "r", stdin);
    freopen("airport.out", "w", stdout);
    int T; io >> T;
    while (T--) solve();
    
    fclose(stdin); fclose(stdout);
    return 0;
}
