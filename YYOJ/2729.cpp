#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e18;
const int N = 1e5 + 5;
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

int n, m, tot;
bool vis[N * 6];
vector<array<int, 2 > > es[N * 6];
ll dis1[N * 6], disn[N * 6], dis[N * 6];

namespace Seg {
    int o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void build(int p, int l, int r) {
        if (l == r) return o[p] = l, void();
        M; build(goL); build(goR); o[p] = ++tot; es[o[ls]].pb({tot, 0}), es[o[rs]].pb({tot, 0});
    }
    inline void upd(int p, int l, int r, int x, int y, const int &u) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return es[o[p]].pb({u, 0});
        M; upd(goL, x, y, u); upd(goR, x, y, u);
    }
}
using namespace Seg;

inline void Dij(ll d[]) {
    memset(vis, 0, sizeof vis);
    priority_queue<pair<ll, int > > q;
    For (i, 1, tot) if (d[i] < INF) q.push({-d[i], i});
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w] : es[u]) if (cmin(d[v], d[u] + w)) q.push({-d[v], v});
    }
}

int main() {
    io >> n >> m; tot = n;
    build(1, 1, n);
    int x, w, l, r;
    while (m--) io >> x >> w >> l >> r, es[++tot].pb({x, w}), upd(1, 1, n, l, r, tot);
    memset(dis1, 31, sizeof dis1); dis1[1] = 0; Dij(dis1);
    memset(disn, 31, sizeof disn); disn[n] = 0; Dij(disn);
    For (i, 1, tot) dis[i] = min(dis1[i] + disn[i], INF); Dij(dis);
    For (i, 1, n) printf("%lld\n", dis[i]<INF? dis[i]: -1);

    return 0;
}
