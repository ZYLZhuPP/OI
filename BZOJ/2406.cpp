#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 405, M = 2e5 + 5, inf = 1e9;

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

int n, m, a[N][N], s[N], L, R, ans;

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

int deg[N], sum;
inline void add(int u, int v, int l, int r) {
    deg[u] -= l; deg[v] += l;
    add(u, v, r - l);
}

inline bool check(int x) {
    en = 1; sum = 0;
    memset(deg, 0, sizeof deg);
    memset(head, 0, sizeof head);
    int s0 = n + m + 1, t0 = s0 + 1;
    For (i, 1, n) add(s0, i, s[i] - x, s[i] + x);
    For (i, 1, m) add(n + i, t0, s[n + i] - x, s[n + i] + x);
    For (i, 1, n) For (j, 1, m) add(i, n + j, L, R);
    int s1 = t0 + 1, t1 = s1 + 1;
    For (i, 1, t0) if (deg[i] > 0) add(s1, i, deg[i]), sum += deg[i]; else if (deg[i] < 0) add(i, t1, -deg[i]);
    add(t0, s0, 0, inf);
    return maxflow(t1, s1, t1) == sum; 
}

int main() {
    io >> n >> m;
    For (i, 1, n) For (j, 1, m) io >> a[i][j], s[i] += a[i][j], s[n + j] += a[i][j];
    io >> L >> R;
    int l = 0, r = 2e5;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%d", ans);

    return 0;
}
