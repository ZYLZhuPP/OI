#include<bits/stdc++.h>
using namespace std;

#define mkp make_pair
#define st first
#define nd second
#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef vector<int > vec;
typedef long long ll;
const int N = 4e5 + 5;
const ll inf = 1e18;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

struct Edge { int to, w; };
vector<Edge > T1[N], T2[N];
int n;
ll ans;

namespace VT {
    int dfn[N], tim, lg[N], st[N][20], stk[N], top;
    ll dep[N];
    vec Tv[N];
    inline bool cmp(const int &a, const int &b) { return dfn[a] < dfn[b]; }
    inline int dmax(const int &a, const int &b) { return cmp(a, b)? a: b; }
    void dfs(int u, int pre) {
        dfn[u] = ++tim;
        st[tim][0] = pre;
        for (auto &[v, w] : T2[u]) if (v ^ pre) dep[v] = dep[u] + w, dfs(v, u);
    }
    void init() {
        dfs(1, 0);
        lg[1] = 0;
        For (i, 2, N - 1) lg[i] = lg[i >> 1] + 1;
        For (j, 1, 19) For (i, 1, n - (1 << j) + 1)
            st[i][j] = dmax(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    int lca(int u, int v) {
        if (u == v) return u;
        if (!cmp(u, v)) swap(u, v);
        int l = dfn[u] + 1, r = dfn[v], k = lg[r - l + 1];
        return dmax(st[l][k], st[r - (1 << k) + 1][k]);
    }
    void ins(int u) {
        if (!top) return void(stk[++top] = u);
        int fu = lca(u, stk[top]);
        if (fu ^ stk[top]) {
            while (cmp(fu, stk[top])) top--;
            int v = stk[top];
            if (fu ^ v) {
                Tv[fu].pb(Tv[v].back()); Tv[v].back() = fu;
                stk[++top] = fu;
            }
        }
        Tv[fu].pb(u); stk[++top] = u;
    }
    void build(vec &p) {
        top = 0;
        if (p[0] ^ 1) ins(1);
        for (auto &u : p) ins(u);
    }
}

namespace VD {
    int sz[N], msz[N], co[N], vis[N];
    ll dep[N], dis[N];
    pair<ll, int > f[N][2];
    void init(int u, int pre) { sz[u] = 1; for (auto &[v, w] : T1[u]) if (v ^ pre) dep[v] = dep[u] + w, init(v, u), sz[u] += sz[v]; }
    int getG(int u, int pre, int n) {
        msz[u] = 0;
        for (auto [v, w] : T1[u]) if (!vis[v] && v ^ pre) {
            msz[u] = max(msz[u], sz[v]);
            if (v = getG(v, u, n)) {
                sz[u] = n - msz[u];
                return v;
            }
        }
        return max(msz[u], n - sz[u]) <= n / 2? sz[u] = n, u: 0;
    }
    void dfs(int u, int pre) {
        for (auto &[v, w] : T1[u]) if (!vis[v] && v ^ pre) {
            co[v] = co[u]; dis[v] = dis[u] + w;
            dfs(v, u);
        }
    }
    void dp(int u) {
        f[u][0] = co[u]? mkp(dep[u] + dis[u], co[u]): mkp(-inf, -1);
        f[u][1] = mkp(-inf, -1);
        ll res = -inf;
        for (auto &v : VT::Tv[u]) {
            dp(v);
            if (f[v][0].nd ^ f[u][0].nd) {
                res = max(res, f[u][0].st + f[v][0].st);
                if (f[v][0] > f[u][0]) f[u][1] = max(f[u][0], f[v][1]), f[u][0] = f[v][0];
                else f[u][1] = max(f[u][1], f[v][0]);
            } else {
                res = max(res, f[u][0].st + f[v][1].st);
                res = max(res, f[u][1].st + f[v][0].st);
                f[u][0] = max(f[u][0], f[v][0]);
                f[u][1] = max(f[u][1], f[v][1]);
            }
        }
        ans = max(ans, res / 2 - VT::dep[u]);
        VT::Tv[u].resize(0);
    }
    void Divide(int u, vec &p) {
        u = getG(u, 0, sz[u]); vis[u] = 1;
        int color = dis[u] = 0;
        co[u] = ++color;
        vec son = {0, u};
        for (auto &[v, w] : T1[u]) if (!vis[v]) {
            co[v] = ++color; son.pb(v); dis[v] = w;
            dfs(v, u);
        }
        VT::build(p);
        dp(1);
        vec o[color + 1];
        for (auto &v : p) o[co[v]].pb(v), co[v] = 0;
        p.resize(0);
        For (i, 2, color) Divide(son[i], o[i]);
    }
}

int main() {
    io >> n;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, T1[u].pb({v, w}), T1[v].pb({u, w});
    For (i, 1, n - 1) io >> u >> v >> w, T2[u].pb({v, w}), T2[v].pb({u, w});
    ans = -inf;
    VT::init();
    VD::init(1, 0);
    For (i, 1, n) ans = max(ans, VD::dep[i] - VT::dep[i]);
    vec p(n); iota(p.begin(), p.end(), 1);
    sort(p.begin(), p.end(), VT::cmp);
    VD::Divide(1, p);
    printf("%lld", ans);

    return 0;
}
