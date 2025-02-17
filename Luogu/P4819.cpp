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

int n, m, dfn[N], low[N], tim, co[N], color, lst[N], deg[N], ans;
int stk[N], top;
vector<int > G[N], pt[N], D[N];

void Tarjan(int u) {
    stk[++top] = u;
    dfn[u] = low[u] = ++tim;
    for (auto &v : G[u]) {
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        color++;
        do co[stk[top]] = color, pt[color].pb(stk[top]);
        while (stk[top--] ^ u);
    }
}

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, G[u].pb(v);
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    int j; For (i, 1, color) for (auto &u : pt[i]) for (auto &v : G[u]) if ((j = co[v]) ^ i && lst[j] ^ i) D[i].pb(j), lst[j] = i, deg[j]++;
    For (i, 1, color) ans += !deg[i];
    For (i, 1, color) if (!deg[i] && pt[i].size() == 1) {
        bool flag = 1;
        for (auto &j : D[i]) flag &= deg[j] > 1;
        if (flag) { ans--; break; }
    }
    printf("%.6lf", 1.0 * (n - ans) / n);

    return 0;
}
