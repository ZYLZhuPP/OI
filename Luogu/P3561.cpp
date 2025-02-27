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

int n, dfn[N], low[N], tim, co[N], color, stk[N], top;
char g[N][N];
vector<int > h[N], ans[N];

inline void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    For (v, 1, n) if (g[u][v]) {
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        color++;
        do co[stk[top]] = color;
        while (stk[top--] ^ u);
    }
}

vector<int > solve(vector<int > v) {
    if (int(v.size()) == 1) return v;
    vector<int > h;
    for (auto &u : v) h.insert(find_if(h.begin(), h.end(), [&](int v) { return g[u][v]; }), u);
    auto it = find_if(h.begin(), h.end(), [&](int v) { return g[v][h[0]]; }) + 1;
    vector<int > c(h.begin(), it);
    while (it != h.end()) {
        auto r = it;
        while (find_if(c.begin(), c.end(), [&](int v) { return g[*r][v]; }) == c.end()) r++;
        auto p = c.begin();
        while (p + 1 != c.end() && !(g[*p][*it] && g[*r][*(p + 1)])) p++;
        c.insert(p==c.end()? c.begin(): p + 1, it, r + 1);
        it = r + 1;
    }
    return c;
}

int main() {
    io >> n;
    For (i, 1, n) For (j, 1, i - 1) io >> g[j][i], g[i][j] = !g[j][i];
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    For (i, 1, n) h[co[i]].pb(i);
    For (i, 1, color) {
        h[i] = solve(h[i]);
        for (auto it = h[i].begin(); it != h[i].end(); ++it) {
            int u = *it;
            ans[u].insert(ans[u].end(), it, h[i].end());
            ans[u].insert(ans[u].end(), h[i].begin(), it);
            rFor (j, i - 1, 1) ans[u].insert(ans[u].end(), h[j].begin(), h[j].end());
        }
    }
    For (i, 1, n) {
        printf("%d", (int)ans[i].size());
        for (auto &u : ans[i]) printf(" %d", u);
        puts("");
    }

    return 0;
}