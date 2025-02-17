#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, inf = 1e9;
template<class C> inline void cmin(C &x, const C &y) { x = y<x? y: x; }
template<class C> inline void cmax(C &x, const C &y) { x = y>x? y: x; }

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

int n, m, q, w[N], pt[N], val[N];
int mx[N], mn[N], Mx, Mn;
ll ans;

namespace VT {
    vector<int > es[N];
    int fa[N][21], dep[N], siz[N], dfn[N], tim, Fa[N], vir[N], cnt, stk[N], top;
    inline void init(int u, int pre) {
        dfn[u] = ++tim; dep[u] = dep[pre] + 1; fa[u][0] = pre; siz[u] = 1;
        For (i, 1, 20) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto &v : es[u]) if (v ^ pre) init(v, u), siz[u] += siz[v];
    }
    inline int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        rFor (i, 20, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
        if (u == v) return u;
        rFor (i, 20, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
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
                    stk[++top] = vir[++cnt] = fu, mn[fu] = inf, mx[fu] = 0, val[fu] = 0;
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
        val[fu] += val[u];
        w[u] = dep[u] - dep[fu];
        ans += 1ll * w[u] * val[u] * (m - val[u]);
        cmin(Mn, mn[fu] + mn[u] + w[u]);
        cmax(Mx, mx[fu] + mx[u] + w[u]);
        cmin(mn[fu], mn[u] + w[u]);
        cmax(mx[fu], mx[u] + w[u]);
    }
}

int main() {
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    init(1, 0);
    io >> q;
    while (q--) {
        ans = 0; Mx = 0; Mn = inf;
        io >> m;
        For (i, 1, m) {
            io >> u;
            mx[u] = mn[u] = 0;
            val[u] = 1;
            vir[i] = pt[i] = u;
        }
        build(m);
        solve();
        printf("%lld %d %d\n", ans, Mn, Mx);
    }
    return 0;
}
