#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, M = 4e6 + 5;
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

int n, m, K, fa[N], tot, id[N][N][2], bg[N], ed[N], tim, stk[M], top, co[M], color, dfn[M], low[M], ans;
vector<int > T[N], G[M];

inline void dfs(int u) {
    bg[u] = ++tim;
    for (auto &v : T[u]) dfs(v);
    ed[u] = tim;
}

inline bool in(int x, int y) { return bg[y] <= bg[x] && bg[x] <= ed[y]; }

inline void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : G[u])
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        color++;
        do co[stk[top]] = color;
        while (stk[top--] ^ u);
    }
}

int main() {
    freopen("ceremony.in", "r", stdin);
    freopen("ceremony.out", "w", stdout);
    io >> n >> m >> K;
    For (i, 2, n) io >> fa[i], T[fa[i]].pb(i);
    dfs(1);
    For (i, 1, m) For (j, 1, n) For (k, 0, 1) id[i][j][k] = ++tot;
    For (i, 1, m) {
        For (j, 2, n) G[id[i][j][1]].pb(id[i][fa[j]][1]), G[id[i][fa[j]][0]].pb(id[i][j][0]);
        For (u, 1, n) {
            for (auto &v : T[u]) {
                if (v ^ T[u][0]) G[id[i][v][1]].pb(tot), G[tot + 1].pb(tot);
                G[++tot].pb(id[i][v][0]);
            }
            reverse(T[u].begin(), T[u].end());
            for (auto &v : T[u]) {
                if (v ^ T[u][0]) G[id[i][v][1]].pb(tot), G[tot + 1].pb(tot);
                G[++tot].pb(id[i][v][0]);
            }
        }
    }
    int r, x, y, u;
    while (K--) {
        io >> r >> x >> y >> u;
        if (r == u) {
            for (auto &v : T[u]) G[id[x][v][1]].pb(id[y][v][0]), G[id[y][v][1]].pb(id[x][v][0]);
            G[id[x][u][0]].pb(id[y][u][1]), G[id[y][u][0]].pb(id[x][u][1]);
        } else if (in(r, u)) {
            int z = r;
            for (auto &v : T[u]) if (!in(r, v)) G[id[x][v][1]].pb(id[y][v][0]), G[id[y][v][1]].pb(id[x][v][0]); else z = v;
            G[id[x][u][0]].pb(id[y][u][1]), G[id[y][u][0]].pb(id[x][u][1]);
            G[id[x][z][1]].pb(id[x][z][0]), G[id[y][z][1]].pb(id[y][z][0]);
        } else {
            for (auto &v : T[u]) G[id[x][v][1]].pb(id[y][v][0]), G[id[y][v][1]].pb(id[x][v][0]);
            G[id[x][u][0]].pb(id[x][u][1]), G[id[y][u][0]].pb(id[y][u][1]);
        }
    }
    For (i, 1, tot) if (!dfn[i]) Tarjan(i);
    For (i, 1, m) For (j, 1, n) if (co[id[i][j][0]] == co[id[i][j][1]]) return puts("-1"), 0;
    For (i, 1, m) {
        ans = 1;
        For (j, 2, n) if (co[id[i][j][1]] < co[id[i][j][0]] && in(j, ans)) ans = j;
        printf("%d%c", ans, " \n"[i==m]);
    }

    fclose(stdin); fclose(stdout);
    return 0;
}
