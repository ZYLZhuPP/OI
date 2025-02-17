#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int T, n, m, dfn[N], dfn_[N], tim, f[N], fa[N], rt;
vector<int > es[N], ans;
multiset<int > se[N];
mt19937 rnd(1145141);

inline bool dfs(int u) {
    dfn[u] = ++tim;
    for (auto &v : es[u]) if (dfn_[v] || (!dfn[v] && dfs(v))) return 1;
    dfn_[u] = tim;
    return 0;
}

inline void dfs0(int u) {
    for (auto &v : es[u]) if (dfn[v] > dfn[u]) {
        dfs0(v);
        if (se[v].size() > se[u].size()) swap(se[u], se[v]);
        for (auto &x : se[v]) se[u].insert(x);
        se[v].clear();
    } else se[u].insert(v);
    if (se[u].count(u)) se[u].erase(u);
    if ((int)se[u].size() > 1) fa[u] = 0;
    else if ((int)se[u].size() == 1) fa[u] = *se[u].begin();
}

inline void solve(int u) {
    if (!~fa[u] || f[fa[u]]) f[u] = 1, ans.pb(u);
    for (auto &v : es[u]) if (dfn[v] > dfn[u]) solve(v);
}

int main() {
    io >> T;
    while (T--) {
        rt = 0; ans.resize(0);
        io >> n >> m;
        For (i, 1, n) es[i].resize(0);
        int u, v;
        For (i, 1, m) io >> u >> v, es[u].pb(v);
        For (i, 1, 100) {
            tim = 0;
            For (i, 1, n) dfn[i] = dfn_[i] = 0;
            u = rnd() % n + 1;
            if (!dfs(u)) { rt = u; break; }
        }
        if (!rt) { puts("-1"); continue; }
        For (i, 1, n) fa[i] = -1, f[i] = 0;
        dfs0(rt); se[rt].clear();
        solve(rt);
        if ((int)ans.size() * 5 < n) { puts("-1"); continue; }
        sort(ans.begin(), ans.end());
        for (auto &x : ans) printf("%d ", x);
        puts("");
    }

    return 0;
}
