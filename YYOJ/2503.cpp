#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, inf  = 1e9;
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

int n, m, pt[N], mn1, mn2, tot, dis1[N], dis2[N];
vector<int > es[N];

inline void bfs(int rt, int dis[]) {
    For (i, 1, n) dis[i] = inf;
    dis[rt] = 0;
    queue<int > q; q.push(rt);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &v : es[u]) if (cmin(dis[v], dis[u] + 1)) q.push(v);
    }
}

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, m) {
        io >> u >> v;
        if (!u || !v) pt[++tot] = u | v;
        else es[u].pb(v), es[v].pb(u);
    }
    bfs(1, dis1); bfs(n, dis2);
    mn1 = mn2 = inf;
    For (i, 1, tot) cmin(mn1, dis1[pt[i]] + 1), cmin(mn2, dis2[pt[i]] + 1);
    For (i, 1, n) {
        int x = min(dis1[n], min(mn1, dis1[i]) + min(mn2, dis2[i]));
        printf("%d\n", x<inf? x: -1);
    }

    return 0;
}
