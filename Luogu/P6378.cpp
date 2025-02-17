#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e6 + 5;
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

int n, m, K, tot, x[N], a[N], b[N];
vector<int > es[N];
int dfn[N], low[N], tim, co[N], color, stk[N], top;

void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : es[u])
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        color++;
        do co[stk[top]] = color;
        while (stk[top--] ^ u);
    }
}

int main() {
    io >> n >> m >> K;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u + n].pb(v), es[v + n].pb(u);
    tot = 2 * n;
    while (K--) {
        io >> m;
        For (i, 1, m) {
            io >> x[i];
            a[i] = ++tot; b[i] = ++tot;
            es[a[i]].pb(x[i] + n); es[b[i]].pb(x[i] + n);
            if (i > 1) es[a[i - 1]].pb(a[i]), es[b[i]].pb(b[i - 1]), es[x[i - 1]].pb(a[i]), es[x[i]].pb(b[i - 1]);
        }
    }
    For (i, 1, tot) if (!dfn[i]) Tarjan(i);
    For (i, 1, n) if (co[i] == co[i + n]) return puts("NIE"), 0;
    puts("TAK");

    return 0;
}
