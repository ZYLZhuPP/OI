#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
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

int n, m, dfn[N], low[N], pt[N], tim, stk[N], top, fa[N], pa[N], tot, s[N], t[N];
bool in[N];
vector<int > es[N], ans;

inline int find(int x) { return x^pa[x]? pa[x] = find(pa[x]): x; }

inline void Tarjan(int u) {
    dfn[u] = low[u] = ++tim, pt[tim] = stk[++top] = u, in[u] = 1;
    for (auto &v : es[u]) {
        if (!dfn[v]) fa[v] = u, Tarjan(v), cmin(low[u], low[v]), pa[v] = u;
        else if (in[v]) {
            int f = find(v);
            if (f == v) tot++, s[u]++, s[fa[v]]--, cmin(low[u], dfn[v]);
            else {
                cmin(low[u], low[v]);
                if (low[v] <= dfn[f]) t[fa[v]]++, t[f]--;
            }
        }
    }
    if (dfn[u] == low[u]) do in[stk[top]] = 0; while (stk[top--] ^ u);
}

int main() {
    freopen("reality.in", "r", stdin);
    freopen("reality.out", "w", stdout);
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v);
    For (i, 1, n) pa[i] = i;
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    rFor (i, n, 1) s[fa[pt[i]]] += s[pt[i]], t[fa[pt[i]]] += t[pt[i]];
    For (i, 1, n) if (s[i] == tot && !t[i]) ans.pb(i);
    printf("%d\n", (int)ans.size());
    for (auto &u : ans) printf("%d ", u);

    fclose(stdin); fclose(stdout);
    return 0;
}