#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;
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

int n, q1, q2, ID, m, dfn[N], low[N], tim, co[N], color, stk[N], top, sz[N];
char g[N][N];
vector<int > es[N];

inline void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : es[u])
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        color++;
        do co[stk[top]] = color, sz[color]++;
        while (stk[top--] ^ u);
    }
}

int main() {
    freopen("starboy.in", "r", stdin);
    freopen("starboy.out", "w", stdout);
    io >> n >> q1 >> q2 >> ID;
    For (i, 1, n) scanf("%s", g[i] + 1);
    For (i, 1, n) For (j, 1, n) if (g[i][j] & 1) es[i].pb(j);
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    For (i, 1, color) sz[i] += sz[i - 1];
    int u;
    while (q2--) {
        io >> u >> m;
        printf("%d\n", sz[co[u]]);
    }

    fclose(stdin); fclose(stdout);
    return 0;
}
