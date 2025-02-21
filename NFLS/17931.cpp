#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e3 + 10, M = 1e4 + 5;
const ll INF = 1e18;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n;

namespace SSP {
    int head[N], nxt[M << 1], to[M << 1], en = 1; ll cap[M << 1], cost[M << 1];
    int cur[N], inq[N], vis[N], S, T; ll dis[N], Cost;
    inline void add(int u, int v, ll f, ll w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f; cost[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0; cost[en] = -w;
    }
    inline bool SPFA(int n) {
        For (i, 1, n) dis[i] = -INF, inq[i] = vis[i] = 0, cur[i] = head[i];
        queue<int > q;
        dis[T] = 0; q.push(T); inq[T] = 1;
        while (!q.empty()) {
            int u = q.front(), v; q.pop(); inq[u] = 0;
            for (int i = head[u]; i; i = nxt[i]) if (cap[i ^ 1])
                if (cmax(dis[v = to[i]], dis[u] + cost[i ^ 1]) && !inq[v]) q.push(v), inq[v] = 1;
        }
        return dis[S] > -INF;
    }
    inline ll dfs(int u, ll r) {
        if (u == T) return Cost += dis[S] * r, r;
        vis[u] = 1;
        ll flow = 0, f; int v;
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
    inline ll Dinic(int n, int s, int t, ll lim) {
        S = s, T = t, Cost = 0;
        ll res = 0;
        while (res < lim && SPFA(n)) res += dfs(S, lim - res);
        return res;
    }
}
using namespace SSP;

int main() {
    io >> n;
    int p1 = 2 * n + 1, p2 = p1 + 1, p3 = p2 + 1, p4 = p3 + 1, s = p4 + 1, t = s + 1, x, y, z;
    For (i, 1, n) io >> x >> y >> z, add(s, i, z, 0), add(i, p1, INF, x + y), add(i, p2, INF, x - y), add(i, p3, INF, -x + y), add(i, p4, INF, -x - y);
    For (i, n + 1, 2 * n) io >> x >> y >> z, add(i, t, z, 0), add(p1, i, INF, -x - y), add(p2, i, INF, -x + y), add(p3, i, INF, x - y), add(p4, i, INF, x + y);
    Dinic(t, s, t, INF);
    printf("%lld", Cost);
    
    return 0;
}