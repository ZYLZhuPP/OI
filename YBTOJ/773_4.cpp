#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
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

int n, m, q, pt[N], is[N];
ll mx[N], f[N][2], ans, s0[N], s1[N];

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
                    stk[++top] = vir[++cnt] = fu,
                    f[fu][0] = mx[fu] = s0[fu] = s1[fu] = 0;
            }
            Fa[u] = fu; stk[++top] = u;
        }
        sort(vir + 1, vir + cnt + 1, cmp);
    }
}
using namespace VT;

void solve() {
    rFor(i, cnt, 1) {
        int u = vir[i], fu = Fa[u];
        if (!is[u]) f[u][0] -= mx[u], f[u][1] = min(s0[u] + 1, s1[u]);
        if (i == 1) { ans = min(f[u][0], f[u][1]); break; }
        if (is[u] && dep[u] == dep[fu] + 1) f[u][1] = n + 1;
        if (is[fu]) {
            f[fu][0] += f[u][1];
            f[fu][1] += f[u][1];
        } else {
            f[fu][0] += f[u][1];
            s0[fu] += min(f[u][1], f[u][0]);
            s1[fu] += f[u][1];
            cmax(mx[fu], f[u][1] - f[u][0]);
        }
    }
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
            f[u][0] = 0; f[u][1] = 1; mx[u] = 0;
            vir[i] = pt[i] = u;
            is[u] = 1;
        }
        build(m);
        solve();
        printf("%lld\n", ans<=n? ans: -1);
        For (i, 1, m) is[pt[i]] = 0;
    }
    return 0;
}
