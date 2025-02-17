#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define st first
#define nd second
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef pair<int, int > P;
const int N = 3e5 + 5, inf = 1e9;
template<class C> inline void cmin(C &x, const C &y) { x = y<x? y: x; }

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

int n, m, q, w[N], ans[N], val[N], pt[N];
P f[N];

namespace VT {
    vector<int > es[N];
    int fa[N][20], dep[N], siz[N], dfn[N], tim, Fa[N], vir[N], cnt, stk[N], top;
    inline void init(int u, int pre) {
        dfn[u] = ++tim; dep[u] = dep[pre] + 1; fa[u][0] = pre; siz[u] = 1;
        For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto &v : es[u]) if (v ^ pre) init(v, u), siz[u] += siz[v];
    }
    inline int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        rFor (i, 19, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
        if (u == v) return u;
        rFor (i, 19, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
    }
    inline int jump(int u, int k) {
        for (int i = 0; i <= 19; ++i, k >>= 1) if (k & 1) u = fa[u][i];
        return u;
    }
    inline bool cmp(const int &x, const int &y) { return dfn[x] < dfn[y]; }
    inline void build(const int &n) {
        top = 0; cnt = n;
        sort(vir + 1, vir + n + 1, cmp);
        For (i, 1, n) {
            int u = vir[i], fu = lca(u, stk[top]);
            if (fu ^ stk[top]) {
                while (dep[stk[top]] > dep[fu]) top--;
                if (fu ^ stk[top])
                    Fa[stk[top + 1]] = fu, Fa[fu] = stk[top],
                    stk[++top] = vir[++cnt] = fu, f[fu] = P(inf, 0);
            }
            Fa[u] = fu; stk[++top] = u;
        }
        sort(vir + 1, vir + cnt + 1, cmp);
    }
}
using namespace VT;

void solve() {
    rFor(i, cnt, 2) {
        int u = vir[i], fu = Fa[u];
        w[u] = dep[u] - dep[fu];
        cmin(f[fu], P(f[u].st + w[u], f[u].nd));
    }
    For (i, 2, cnt) {
        int u = vir[i], fu = Fa[u];
        cmin(f[u], P(f[fu].st + w[u], f[fu].nd));
    }
    For (i, 1, cnt) {
        int u = vir[i];
        val[u] = siz[u];
        if (i == 1) {
            ans[f[u].nd] += n - siz[u];
            continue;
        }
        int fu = Fa[u], v = siz[jump(u, dep[u] - dep[fu] - 1)];
        val[fu] -= siz[v];
        if (f[u].nd == f[fu].nd) ans[f[u].nd] += siz[v] - siz[u];
        else {
            int x = (dep[u] - dep[fu] + f[fu].st - f[u].st - (f[fu].nd < f[u].nd)) >> 1;
            x = jump(u, x);
            ans[f[u].nd] += siz[x] - siz[u];
            ans[f[fu].nd] += siz[v] - siz[x];
        }
    }
    For (i, 1, cnt) ans[f[vir[i]].nd] += val[vir[i]];
}

int main() {
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    init(1, 0);
    io >> q;
    while (q--) {
        io >> m;
        For (i, 1, m) {
            io >> u;
            ans[u] = 0;
            f[u] = P(0, u);
            vir[i] = pt[i] = u;
        }
        build(m);
        solve();
        For (i, 1, m) printf("%d ", ans[pt[i]]);
        puts("");
    }
    return 0;
}
