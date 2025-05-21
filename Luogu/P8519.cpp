#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

int n, m, mn, q[N << 1], fa[N], a[N];
bool vis[N], done[N], co[N];
vector<int > Co, pt[N], res;
vector<array<int, 2 > > es[N];

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

inline void clr() {
    for (auto &w : Co) pt[w].resize(0), co[w] = 0;
    Co.resize(0);
}

inline void bfs(int rt) {
    vector<int > Q;
    int h = 1, t = 0; q[++t] = rt;
    while (h <= t) {
        int u = q[h++];
        if (find(u) ^ rt) return fa[rt] = find(u), vis[find(u)] = 1, clr();
        if (vis[u]) continue;
        vis[u] = 1; Q.pb(u);
        if (!co[a[u]]) {
            co[a[u]] = 1; Co.pb(a[u]);
            for (auto &v : pt[a[u]]) q[++t] = v;
        }
        for (auto &[v, w] : es[u]) if (!co[w]) pt[w].pb(v), Co.pb(w); else if (!vis[v] || find(v) ^ rt) q[++t] = v;
    }
    done[rt] = 1;
    if (cmin(mn, (int)Q.size())) res = Q;
    else if (mn == (int)Q.size()) for (auto &u : Q) res.pb(u);
    clr();
}

vector<int > find_reachable(vector<int > r, vector<int > u, vector<int > v, vector<int > c) {
    n = r.size(), m = c.size(); mn = n + 1;
    For (i, 0, n - 1) a[i] = r[i], fa[i] = i;
    For (i, 0, m - 1) es[u[i]].pb({v[i], c[i]}), es[v[i]].pb({u[i], c[i]});
    while (1) {
        bool flag = 1;
        For (i, 0, n - 1) vis[i] = 0;
        For (i, 0, n - 1) if (find(i) == i && !vis[i] && !done[i]) bfs(i), flag = 0;
        if (flag) break;
    }
    vector<int > ans(n);
    for (auto &x : res) ans[x] = 1;
    return ans;
}
