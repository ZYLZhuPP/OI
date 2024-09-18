#include<bits/stdc++.h>
using namespace std;

#define nd second
#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef array<int, 3 > P;
const int N = 2e5 + 5, inf = 1e9;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
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
	inline bool operator ~ () { return ~c; }
} io;

namespace Seg {
    int o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(int p, int l, int r, int x, int y, const int &v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return cmin(o[p], v), void();
        M; upd(goL, x, y, v); upd(goR, x, y, v);
    }
    inline int query(int p, int l, int r, int x) {
        if (l > x || r < x) return inf;
        if (l == r) return o[p];
        M; return min(o[p], min(query(goL, x), query(goR, x)));
    }
}
using namespace Seg;

int n, m, tot, on[N], pt[N], mn[N], mx[N], dis1[N], dis2[N], vis[N], ans, cnt;
vector<P > G[N];
P es[N];

inline void Dij(int rt, int dis[]) {
    memset(vis, 0, sizeof vis);
    priority_queue<pair<int, int > > q;
    dis[rt] = 0; q.push({0, rt});
    while (!q.empty()) {
        int u = q.top().nd; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w, id] : G[u]) if (!vis[v] && cmin(dis[v], dis[u] + w)) q.push({-dis[v], v});
    }
}

int main() {
    memset(dis1, 63, sizeof dis1);
    memset(dis2, 63, sizeof dis2);
    memset(o, 63, sizeof o);
    io >> n >> m;
    if (n == 1) return printf("0 %d", m), 0;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, es[i] = {u, v, w}, G[u].pb({v, w, i}), G[v].pb({u, w, i});
    For (i, 1, n) mn[i] = n, pt[i] = i;
    Dij(1, dis1); Dij(n, dis2);
    for (int u = 1; mn[u] = mx[u] = ++tot, u ^ n;) for (auto &[v, w, id] : G[u]) if (dis2[u] == dis2[v] + w) { u = v; on[id] = 1; break; }
    sort(pt + 1, pt + n + 1, [&](int x, int y) { return dis1[x] < dis1[y]; });
    For (i, 1, n) {
        int u = pt[i];
        for (auto &[v, w, id] : G[u]) if (!on[id] && dis1[v] == dis1[u] + w) cmin(mn[v], mn[u]);
    }
    sort(pt + 1, pt + n + 1, [&](int x, int y) { return dis2[x] < dis2[y]; });
    For (i, 1, n) {
        int u = pt[i];
        for (auto &[v, w, id] : G[u]) if (!on[id] && dis2[v] == dis2[u] + w) cmax(mx[v], mx[u]);
    }
    For (i, 1, m) if (!on[i]) {
        auto [u, v, w] = es[i];
        if (mn[u] < mx[v]) upd(1, 1, n, mn[u], mx[v] - 1, dis1[u] + dis2[v] + w);
        if (mn[v] < mx[u]) upd(1, 1, n, mn[v], mx[u] - 1, dis1[v] + dis2[u] + w);
    }
    ans = dis1[n];
    For (i, 1, tot - 1) {
        int x = query(1, 1, n, i);
        if (cmax(ans, x)) cnt = 1;
        else if (ans == x) cnt++;
    }
    printf("%d %d", ans, ans>dis1[n]? cnt: m);

    return 0;
}
