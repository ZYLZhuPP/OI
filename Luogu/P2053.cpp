#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, M = 5e5 + 5, inf = 1e9;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
	char c; int f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, s, t, u, v, a[100][15];

namespace SSP {
    int head[N], nxt[M << 1], to[M << 1], en = 1, tot; int cap[M << 1], cost[M << 1];
    int cur[N], inq[N], vis[N], S, T, is[N]; int dis[N], Cost;
    void add(int u, int v, int f, int w) {
        nxt[++en] = head[u]; head[u] = en; to[en] = v; cap[en] = f; cost[en] = w;
        nxt[++en] = head[v]; head[v] = en; to[en] = u; cap[en] = 0; cost[en] = -w;
    }
    bool SPFA(int n) {
        For (i, 1, n) dis[i] = inf, inq[i] = vis[i] = 0, cur[i] = head[i];
        queue<int > q;
        dis[T] = 0; q.push(T); inq[T] = 1;
        while (!q.empty()) {
            int u = q.front(), v; q.pop(); inq[u] = 0;
            for (int i = head[u]; i; i = nxt[i]) if (cap[i ^ 1])
                if (cmin(dis[v = to[i]], dis[u] + cost[i ^ 1]) && !inq[v]) q.push(v), inq[v] = 1;
        }
        return dis[S] < inf;
    }
    int dfs(int u, int r) {
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
    int Dinic(int s, int t) {
        S = s, T = t, Cost = 0;
        int res = 0;
        while (SPFA(tot)) res += dfs(S, inf);
        return res;
    }
}
using namespace SSP;

int main() {
    io >> m >> n;
    int s0 = n + 1, t0 = s0 + 1; tot = t0;
    For (i, 1, n) add(s0, i, 1, 0);
    For (i, 1, n) For (j, 1, m) io >> a[i][j];
    For (j, 1, m) For (k, 1, n) {
        tot++; add(tot, t0, 1, 0);
        For (i, 1, n) add(i, tot, 1, k * a[i][j]);
    }
    Dinic(s0, t0);
    printf("%.2f", 1.0 * Cost / n);

    return 0;
}
