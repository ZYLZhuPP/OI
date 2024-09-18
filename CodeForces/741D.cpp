#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, M = 5e6 + 5;
inline void cmax(int &x, const int &y) { x = y>x? y: x; }

struct Edge { int to, w; };
vector<Edge > T[N];
int n, f[M], ans[N], fa[N];
int dfn[N], dfn_[N], sz[N], id[N], dep[N], son[N], tim, dis[N];

void dfs0(int u) {
    dfn[u] = ++tim; id[tim] = u; sz[u] = 1;
    for (auto &[v, w] : T[u]) {
        dis[v] = dis[u] ^ w; dep[v] = dep[u] + 1;
        dfs0(v); sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
    dfn_[u] = tim;
}

inline void upd(int rt, int u) {
    if (~f[dis[u]]) cmax(ans[rt], f[dis[u]] + dep[u] - 2 * dep[rt]);
    For (i, 0, 21) {
        int x = dis[u] ^ (1 << i);
        if (~f[x]) cmax(ans[rt], f[x] + dep[u] - 2 * dep[rt]);
    }
}

void solve(int u) {
    for (auto &[v, w] : T[u]) if (v ^ son[u]) solve(v), cmax(ans[u], ans[v]);
    if (son[u]) solve(son[u]), cmax(ans[u], ans[son[u]]);
    upd(u, u); cmax(f[dis[u]], dep[u]);
    for (auto &[v, w] : T[u]) if (v ^ son[u]) {
        For (i, dfn[v], dfn_[v]) upd(u, id[i]);
        For (i, dfn[v], dfn_[v]) cmax(f[dis[id[i]]], dep[id[i]]);
    }
    if (u ^ son[fa[u]]) For (i, dfn[u], dfn_[u]) f[dis[id[i]]] = -1;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    char c;
    For (i, 2, n) {
        cin >> fa[i] >> c;
        T[fa[i]].pb({i, 1 << (c - 'a')});
    }
    dfs0(1);
    memset(f, -1, sizeof f);
    solve(1);
    For (i, 1, n) printf("%d ", ans[i]);

    return 0;
}