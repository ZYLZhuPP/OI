#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 5e4 + 5;

int n, m, u, v, rt[N], ans;
lf w, E;

namespace LT {
    struct Node {
        int l, r, d, v; lf w;
        Node(int v = 0, lf w = 0): v(v), w(w) { l = r = d = 0; }
    } o[N * 20];
    int tot;
#define ls o[p].l
#define rs o[p].r
    inline void up(int p) { if (o[ls].d < o[rs].d) swap(ls, rs); o[p].d = o[rs].d + 1; }
    inline int merge(int p, int q) {
        if (!p || !q) return p | q;
        if (o[q].w < o[p].w) swap(p, q);
        o[++tot] = o[p]; p = tot;
        rs = merge(rs, q); up(p);
        return p;
    }
    inline void ins(int &p, int v, lf w) {
        int q = ++tot; o[q] = Node(v, w);
        p = merge(p, q);
    }
}
using namespace LT;

struct P {
    int x; lf v;
    P (int x = 0, lf v = 0): x(x), v(v) { }
    inline bool operator < (const P &a) const { return v > a.v; } //small root heap
};
priority_queue<P > q;

struct Edges {
    vector<P > es[N];
    inline void add(int u, int v, lf w) { es[u].pb({v, w}); }
} G, T, nT;

bool vis[N];
lf dis[N];
inline void Dij(int s) {
    q.push({s, 0});
    while (!q.empty()) {
        int u = q.top().x; lf w = q.top().v; q.pop();
        if (vis[u]) continue;
        vis[u] = 1; dis[u] = w;
        for (auto &e : G.es[u]) q.push({e.x, w + e.v});
    }
    memset(vis, 0, sizeof vis);
    For (u, 1, n) for (auto &e : G.es[u])
        if (!vis[e.x] && dis[e.x] == dis[u] + e.v)
            T.add(u, e.x, e.v), vis[e.x] = 1;
        else nT.add(e.x, u, e.v);
}

inline void dfs(int u, int pre) {
    if (u ^ n) {
        for (auto &e : nT.es[u]) {
            int v = e.x; lf w = e.v;
            ins(rt[u], v, w + dis[v] - dis[u]);
        }
        rt[u] = merge(rt[u], rt[pre]);
    }
    for (auto &e : T.es[u]) dfs(e.x, u);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> E; //E = the sum of the shortest k dist
    For (i, 1, m) cin >> u >> v >> w, G.add(v, u, w);
    Dij(n);
    if (E < dis[1]) return puts("0"), 0;
    E -= dis[1]; ans++;
    dfs(n, 0);
    if (rt[1]) q.push({rt[1], o[rt[1]].w});
    while (!q.empty()) {
        int p = q.top().x; lf w = q.top().v; q.pop();
        if (E < w + dis[1]) break;
        E -= w + dis[1]; ans++;
        if (ls) q.push({ls, w - o[p].w + o[ls].w});
        if (rs) q.push({rs, w - o[p].w + o[rs].w});
        int v = rt[o[p].v];
        if (v) q.push({v, w + o[v].w});
    }
    cout << ans;

    return 0;
}
