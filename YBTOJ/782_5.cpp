#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e4 + 5, inf = 1e9;

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

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

namespace Tree {
    int dfn[N], dfn_[N], tim, dep[N], fa[N][18];
    vector<int > T[N];
    void dfs(int u, int pre) {
        dfn[u] = ++tim; fa[u][0] = pre; dep[u] = dep[pre] + 1;
        For (i, 1, 17) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto &v : T[u]) if (v ^ pre) dfs(v, u);
        dfn_[u] = tim;
    }
    inline int jump(int u, int x) { rFor (i, 17, 0) if (x >> i & 1) u = fa[u][i]; return u; }
    inline int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        u = jump(u, dep[u] - dep[v]);
        if (u == v) return u;
        rFor (i, 17, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
    }
}
using namespace Tree;

struct OP {
    int x, y, Y, d, v;
    bool operator < (const OP &a) const { return x^a.x? x<a.x: abs(d)>abs(a.d); }
};
vector<OP > ops;

int n, p, q, ans[N];

inline void solve(vector<OP > &o, int l, int r) {
    if (o.empty()) return;
    if (l == r) { for (auto &x : o) if (!x.d) ans[x.v] = l; return; }
    int m = (l + r) >> 1;
    vector<OP > L, R;
    for (auto &[x, y, Y, d, v] : o)
        if (d) {
            if (v <= m) upd(y, d), upd(Y + 1, -d), L.pb({x, y, Y, d, v});
            else R.pb({x, y, Y, d, v});
        } else {
            int p = query(y);
            if (Y <= p) L.pb({x, y, Y, d, v});
            else R.pb({x, y, Y - p, d, v});
        }
    o.resize(0);
    for (auto &[x, y, Y, d, v] : L) if (d && v <= m) upd(y, -d), upd(Y + 1, d);
    solve(L, l, m); solve(R, m + 1, r);
}

inline void add(int x, int X, int y, int Y, int v) {
    ops.pb({x, y, Y, 1, v});
    ops.pb({X + 1, y, Y, -1, v});
}

int main() {
    io >> n >> p >> q;
    int u, v, x;
    For (i, 1, n - 1) io >> u >> v, T[u].pb(v), T[v].pb(u);
    dfs(1, 0);
    For (i, 1, p) {
        io >> u >> v >> x;
        if (dfn[u] > dfn[v]) swap(u, v);
        int f = lca(u, v);
        if (f == u) {
            int w = jump(v, dep[v] - dep[u] - 1);
            add(1, dfn[w] - 1, dfn[v], dfn_[v], x);
            if (dfn_[w] < n) add(dfn[v], dfn_[v], dfn_[w] + 1, n, x);
        } else add(dfn[u], dfn_[u], dfn[v], dfn_[v], x);
    }
    For (i, 1, q) {
        io >> u >> v >> x;
        if (dfn[u] > dfn[v]) swap(u, v);
        ops.pb({dfn[u], dfn[v], x, 0, i});
    }
    sort(ops.begin(), ops.end());
    solve(ops, 0, inf);
    For (i, 1, q) printf("%d\n", ans[i]);

    return 0;
}
