#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;
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

vector<int > G[N], es[N], R[N];
vector<pair<int, int > > E;
map<pair<int, int >, bool > Ans;
set<int > S[N];
int n, m, vis[N], cut[N], ans;
int dep[N], fa[N], sz[N], dfn[N], top[N], son[N], tim, pos[N], id[N];
int mx[N], mn[N];

struct Seg {
    int M, k, o[N << 2];
    inline void upd(int p) { o[p] = min(o[p << 1], o[p << 1 | 1]); }
    inline void build(int n, vector<int > &A) {
        k = 0, M = 1;
        while (M < n) M <<= 1, k++;
        For (i, 1, M + M) o[i] = n + 1;
        For (i, 1, n) o[i + M - 1] = A[i];
        rFor (i, M - 1, 1) upd(i);
    }
    inline int qmin(int l, int r) {
        int res = n + 1;
        for (l += M - 1, r += M; l < r; l >>= 1, r >>= 1) {
            if (l & 1) cmin(res, o[l++]);
            if (r & 1) cmin(res, o[--r]);
        }
        return res;
    }
} T;

inline void dfs1(int u, int pre) {
    dep[u] = dep[pre] + 1, fa[u] = pre, sz[u] = 1;
    for (int &v : G[u]) if (v ^ pre) {
        dfs1(v, u), sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

inline void dfs2(int u, int tp) {
    top[u] = tp, dfn[u] = ++tim, id[tim] = u;
    if (son[u]) dfs2(son[u], tp);
    for (int &v : G[u]) if (v ^ fa[u] && v ^ son[u]) dfs2(v, v);
}

inline int getnode(int u, int v) {
    int x = dep[u] + 1;
    while (dep[top[v]] > x) v = fa[top[v]];
    int d = dep[v] - x;
    return id[dfn[v] - d];
}

struct BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x <= n; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
    inline void add(int l, int r, const int &d) { if (l <= r) upd(r + 1, -d), upd(l, d); }
} B;

inline void build(int u, int pre) {
    vis[u] = 1;
    for (int &v : es[u]) {
        if (!vis[v]) dep[v] = dep[u] + 1, build(v, u), G[u].emplace_back(v);
        else if (dep[v] < dep[u] && v ^ pre) R[u].emplace_back(v);
    }
}

inline void merge(set<int > &A, set<int > &B) {
    if (A.size() < B.size()) swap(A, B);
    for (auto &x : B) A.insert(x);
    B.clear();
}

inline void getlow(int u) {
    for (int &v : G[u]) getlow(v), merge(S[u], S[v]);
    for (int &v : R[u]) S[u].insert(dep[v]);
    S[u].erase(S[u].lower_bound(dep[u] - 1), S[u].end());
    if (S[u].size()) mx[u] = *--S[u].end(), mn[u] = *S[u].begin();
    else mx[u] = 0, mn[u] = n + 1;
}

inline void upd(int u, int v) { Ans[{u, v}] = Ans[{v, u}] = 1; }
inline void solve(int u) {
    if (u == 1) {
        if (G[u].size() >= 3) return;
        if (G[u].size() == 2) { for (int &v : G[u]) if (sz[v] == 1) upd(u, v); }
        if (G[u].size() == 1) {
            int v = G[u][0];
            if (G[v].size() <= 1) upd(u, v);
        }
        return;
    }
    for (int &v : G[u]) {
        if (mn[v] == mx[v]) vis[mn[v]] = 1;
        B.add(mn[v] + 1, mx[v] - 1, 1);
    }
    for (int &v : G[u]) {
        if (mn[v] >= dep[u]) cut[u]--;
        if (cut[u] == 0) {
            bool chk = 1;
            for (int &v : G[v]) if (mn[v] >= dep[u]) chk = 0;
            if (chk) upd(u, v);
        }
        if (mn[v] >= dep[u]) cut[u]++;
    }

    if (cut[u] >= 1) goto ED2;
    for (int &v : R[u]) {
        int x = getnode(v, u);
        if (mn[x] >= dep[v]) cut[v]--;
        if (cut[v] == 0) {
            if (vis[dep[v]]) goto ED;
            if (B.query(dep[v]) >= 1) { upd(u, v); goto ED; }
            if (v == 1) { upd(u, v); goto ED; }
            if (T.qmin(dfn[x], dfn[u] - 1) < dep[v] || T.qmin(dfn[u] + sz[u], dfn[x] + sz[x] - 1) < dep[v]) upd(u, v);
        }
    ED:
        if (mn[x] >= dep[v]) cut[v]++;
    }

ED2:
    for (int &v : G[u]) {
        if (mn[v] == mx[v]) vis[mn[v]] = 0;
        B.add(mn[v] + 1, mx[v] - 1, -1);
    }
}

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, m) {
        io >> u >> v;
        E.emplace_back(u, v);
        es[u].emplace_back(v), es[v].emplace_back(u);
    }

    build(1, 0);
    dfs1(1, 0), dfs2(1, 1);

    vector<int > val(n + 1, n + 1);
    For (u, 1, n) for (int &v : R[u]) cmin(val[dfn[u]], dep[v]);
    T.build(n, val);

    getlow(1);

    For (u, 1, n) for (int &v : G[u]) cut[u] += (mn[v] >= dep[u]);
    memset(vis, 0, sizeof vis);
    For (i, 1, n) solve(i);
    for (auto &[u, v] : E) ans += !Ans[{u, v}];
    printf("%d", ans);

    return 0;
}
