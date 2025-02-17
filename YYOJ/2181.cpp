#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 6e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
template<class C> inline void cmax(C &x, const C &y) { y>x? x=y: 0; }
template<class C> inline void cmin(C &x, const C &y) { y<x? x=y: 0; }

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, dfn[N], tim, dep[N], dis[N], sz[N], msz[N], vis[N], bel[N], st[N][20], lg2[N];
int sum, s1[N], s2[N], m[N], cnt[N], Sz, Mn, G;
int im[N], stk[N], top, Fa[N];
vector<int > T1[N], T2[N], T[N], pt[N], vir;

inline int dmin(int u, int v) { return dep[u]<dep[v]? u: v; }

inline int lca(int u, int v) {
    if (!v) return 0;
    u = dfn[u]; v = dfn[v];
    if (u > v) swap(u, v);
    int x = lg2[v - u + 1];
    return dmin(st[u][x], st[v - (1 << x) + 1][x]);
}

inline void build() {
    int n = vir.size(); top = 0;
    For (i, 0, n - 1) {
        int u = vir[i], fu = lca(u, stk[top]); im[u] = 1;
        //cerr << u << " " << stk[top] << endl;
        if (fu ^ stk[top]) {
            while (dep[stk[top]] > dep[fu]) top--;
            if (fu ^ stk[top])
                Fa[stk[top + 1]] = fu, Fa[fu] = stk[top],
                vir.pb(stk[++top] = fu);
        }
        Fa[u] = fu; stk[++top] = u;
    }
    for (auto &u : vir) if (Fa[u]) T[Fa[u]].pb(u);
}

inline void merge(int u, int v, int x) {
    //cerr << x << endl;
    //cerr << s1[u] << " " << s2[u] << " " << m[u] << " " << cnt[u] << endl;
    //cerr << s1[v] << " " << s2[v] << " " << m[v] << " " << cnt[v] << endl;
    add(sum, mo(ml(x, ml(s1[u], cnt[v])) + ml(x, ml(s1[v], cnt[u]))));
    add(sum, mo(ml(m[u], cnt[v]) + ml(m[v], cnt[u])));
    add(sum, mo(ml(s1[u], s2[v]) + ml(s2[u], s1[v])));
    add(s1[u], s1[v]);
    add(s2[u], s2[v]);
    add(m[u], m[v]);
    add(cnt[u], cnt[v]);
    //cerr << u << " " << v << " " << sum << endl;
}

inline void dfs(int u) {
    if (im[u]) {
        s1[u] = dis[u]; s2[u] = dep[u]; m[u] = ml(dis[u], dep[u]);
        cnt[u] = 1;
    } else s1[u] = s2[u] = m[u] = cnt[u] = 0;
    //cerr << u << endl;
    for (auto &v : T[u]) dfs(v), merge(u, v, -2 * dep[u]);
}

inline void init_sz(int u, int pre) {
    sz[u] = 1;
    for (auto &v : T1[u]) if (v ^ pre) init_sz(v, u), sz[u] += sz[v];
}

inline int getG(int u, int pre, int n) {
    msz[u] = 0;
    for (auto &v : T1[u]) if (!vis[v] && v ^ pre) {
        cmax(msz[u], sz[v]);
        int x = getG(v, u, n);
        if (x) {
            sz[u] = n - msz[u];
            return x;
        }
    }
    return max(msz[u], n - sz[u]) <= n / 2? sz[u] = n, u: 0;
}

inline void get_dis(int u, int pre) {
    dis[u] = dis[pre] + 1; bel[u] = pre^G? bel[pre]: u;
    for (auto &v : T1[u]) if (!vis[v] && v ^ pre) get_dis(v, u);
}

inline int solve(int u) {
    if (sz[u] == 1) return 0;
    sum = 0;
    vir = pt[u];
    build();
    dfs(stk[1]);
    //cerr << endl;
    for (auto &v : vir) T[v].resize(0), im[v] = 0;
    return sum;
}

inline int Divide(int u) {
    if (sz[u] == 1) return 0;
    int res = 0;
    G = getG(u, 0, sz[u]);
    swap(pt[G], pt[u]);
    //cerr << G << endl;
    get_dis(G, 0);
    res = solve(G);
    for (auto &v : pt[G]) if (v ^ G) pt[bel[v]].pb(v);
    pt[G].resize(0);
    //cerr << "!" << res << endl;
    vis[G] = 1;
    for (auto &v : T1[G]) if (!vis[v]) add(res, -solve(v));
    //cerr << "!" << res << endl;
    for (auto &v : T1[G]) if (!vis[v]) add(res, Divide(v));
    return res;
}

inline void dfs0(int u, int pre) {
    dfn[u] = ++tim; pt[1].pb(u); dep[u] = dep[pre] + 1; st[tim][0] = u;
    for (auto &v : T2[u]) if (v ^ pre) dfs0(v, u), st[++tim][0] = u;
}

inline void init_lca() {
    lg2[1] = 0; For (i, 2, N - 1) lg2[i] = lg2[i >> 1] + 1;
    For (j, 1, 19) For (i, 1, tim - (1 << j) + 1) st[i][j] = dmin(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int main() {
    dis[0] = -1;
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, T1[u].pb(v), T1[v].pb(u);
    For (i, 1, n - 1) io >> u >> v, T2[u].pb(v), T2[v].pb(u);
    dfs0(1, 0);
    init_lca();
    init_sz(1, 0);
    printf("%d", Divide(1));
    
    return 0;
} 
