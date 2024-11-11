#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 6e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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
    int o[N], lim, stk[N << 2], top;
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int d) { stk[++top] = x; for (x++; x; x -= lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (x++; x <= lim; x += lowbit(x)) r += o[x]; return r; }
    inline void clear() { while (top) { int x = stk[top--]; for (x++; x; x -= lowbit(x)) o[x] = 0; } }
}
using namespace BIT;

int n, q, U[N], V[N], ans[N], f[N], g[N], op[N];
vector<array<int, 3 > > qs[N];
vector<int > es[N];

namespace VD {
    int sz[N], msz[N], pt[N], tot, vis[N], co[N], G;
    inline void init(int u, int pre) { sz[u] = 1; for (auto &v : es[u]) if (v ^ pre) init(v, u), sz[u] += sz[v]; }
    inline int getG(int u, int pre, int n) {
        msz[u] = 0;
        for (auto v : es[u]) if (!vis[v] && v ^ pre) {
            cmax(msz[u], sz[v]);
            if (v = getG(v, u, n)) return sz[u] = n - msz[u], v;
        }
        return max(msz[u], n - sz[u]) <= n / 2? sz[u] = n, u: 0;
    }
    inline void calc(vector<array<int, 3 > > &qs, int k) {
        f[G] = g[G] = 0;
        int n = qs.size(); lim = n + 1;
        rFor (i, n, 1) {
            auto [op, u, v] = qs[i - 1];
            if (op == 1) continue;
            if (sz[u] < sz[v]) swap(u, v);
            if (u == G) f[v] = i;
            else f[v] = f[u];
        }
        if (k > 0) upd(g[G], 1);
        For (i, 1, n) {
            auto [op, u, v] = qs[i - 1];
            if (op == 1) { if (~f[u] && f[u] <= i) ans[v] += k * query(f[u]); }
            else {
                if (k > 0) upd(g[G], -1), upd(g[G] = i, 1); else g[G] = i;
                if (sz[u] < sz[v]) swap(u, v);
                if (g[u] > g[v]) {
                    if (~g[v]) upd(g[v], -1);
                    upd(g[v] = g[u], 1);
                }
            }
        }
        clear();
    }
    inline void dfs(int u, int pre, int color) { pt[++tot] = u; co[u] = color; for (auto &v : es[u]) if (!vis[v] && v ^ pre) dfs(v, u, color); }
    inline void Divide(int u) {
        G = getG(u, 0, sz[u]); vis[G] = 1; swap(qs[u], qs[G]);
        pt[tot = 1] = G; for (auto &v : es[G]) if (!vis[v]) dfs(v, 0, v);
        For (i, 1, tot) f[pt[i]] = g[pt[i]] = -1;
        calc(qs[G], 1);
        for (auto &[op, u, v] : qs[G]) {
            if (op == 1) { if (u ^ G) qs[co[u]].pb({op, u, v}); }
            else {
                if (sz[u] < sz[v]) swap(u, v);
                qs[co[v]].pb({op, u, v});
            }
        }
        For (i, 1, tot) f[pt[i]] = g[pt[i]] = -1;
        for (auto &v : es[G]) if (!vis[v]) calc(qs[v], -1), qs[v].resize(0);
        for (auto &[op, u, v] : qs[G]) {
            if (op == 1) { if (u ^ G) qs[co[u]].pb({op, u, v}); }
            else {
                if (sz[u] < sz[v]) swap(u, v);
                if (u ^ G) qs[co[v]].pb({op, u, v});
            }
        }
        qs[G].resize(0);
        for (auto &v : es[G]) if (!vis[v]) Divide(v);
    }
}
using namespace VD;

int main() {
    io >> n >> q;
    For (i, 1, n - 1) io >> U[i] >> V[i], es[U[i]].pb(V[i]), es[V[i]].pb(U[i]);
    int x;
    For (i, 1, q) {
        io >> op[i] >> x;
        if (op[i] == 1) qs[1].pb({1, x, i});
        else qs[1].pb({2, U[x], V[x]});
    }
    init(1, 0); Divide(1);
    For (i, 1, q) if (op[i] == 1) printf("%d\n", ans[i]);

    return 0;
}
