#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int n, m, q, K, dfn[N], low[N], tim, co[N], color, stk[N], top, tot, vis[N];
vector<int > es[N], pt[N], G[N];
vector<vector<int > > id;
char s[N];

inline void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : es[u])
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    if (dfn[u] == low[u]) {
        color++;
        do co[stk[top]] = color, pt[color].pb(stk[top]);
        while (stk[top--] ^ u);
    }
}

inline bool dfs(int u, int goal) {
    if (u == goal) return 1;
    for (auto &v : G[u]) if (dfs(v, goal)) return 1;
    return 0;
}

int main() {
    io >> n >> m >> K >> q;
    id.resize(n + 2, vector<int >(m + 2, 0));
    For (i, 1, n) {
        scanf("%s", s + 1);
        For (j, 1, m) if (s[j] == '.') id[i][j] = ++tot;
    }
    For (i, 1, n) For (j, 1, m) if (id[i][j]) {
        For (k, 0, 3) {
            int x = i + dx[k], y = j + dy[k];
            if (id[x][y]) es[id[i][j]].pb(id[x][y]);
        }
    }
    int x, y, X, Y;
    For (i, 1, K) io >> x >> y >> X >> Y, es[id[x][y]].pb(id[X][Y]);
    For (i, 1, tot) if (!dfn[i]) Tarjan(i);
    For (i, 1, color) for (auto &u : pt[i]) for (auto &v : es[u]) if (co[v] ^ i && vis[co[v]] ^ i) G[i].pb(co[v]), vis[co[v]] = i;
    while (q--) {
        io >> x >> y >> X >> Y;
        int u = id[x][y], v = id[X][Y];
        printf("%d\n", dfs(co[u], co[v]));
    }

    return 0;
}
