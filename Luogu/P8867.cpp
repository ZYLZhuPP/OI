#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5, M = 1e6 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
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

vector<int > G[N], T[N];
int n, m, dfn[N], low[N], color, tim, co[N], cnt[N], stk[N], top;
int f[N], _2[M], e[N], ans;

inline void Tarjan(int u, int pre) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : G[u]) if (v ^ pre) {
        if (!dfn[v]) Tarjan(v, u), cmin(low[u], low[v]);
        else cmin(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        color++;
        do co[stk[top]] = color, cnt[color]++;
        while (stk[top--] ^ u);
    }
}

inline void dfs(int u, int pre) {
    f[u] = _2[cnt[u]];
    for (auto &v : T[u]) if (v ^ pre) {
        dfs(v, u);
        mul(f[u], _2[e[v] + 1] + f[v]);
        e[u] += e[v] + 1;
    }
    add(f[u], -_2[e[u]]);

    int x = f[u];
    for (auto &v : T[u]) if (v ^ pre) add(x, -ml(f[v], _2[e[u] - e[v] - 1]));
    add(ans, ml(x, _2[color - 1 - e[u]]));
}

int main() {
    _2[0] = 1; For (i, 1, M - 1) _2[i] = mo(_2[i - 1] << 1);
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, G[u].pb(v), G[v].pb(u);
    Tarjan(1, 0);
    For (u, 1, n) for (auto &v : G[u]) if (co[u] ^ co[v]) T[co[u]].pb(co[v]);
    dfs(1, 0);
    printf("%d", ml(ans, _2[m - e[1]]));

    return 0;
}