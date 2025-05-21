#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 1000002022;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

int n, m, w[N], g[N], f[N], sz[N], pre[N], suf[N];
vector<int > T[N];

namespace Seg {
    int S[N << 2], s[N << 2]; bool t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define Mid int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { s[p] = mo(s[ls] + s[rs]); }
    inline void build(int p, int l, int r) {
        if (l == r) return S[p] = f[l], void();
        Mid; build(goL); build(goR); S[p] = mo(S[ls] + S[rs]);
    }
    inline void mark(int p) { s[p] = mo(S[p] - s[p]); t[p] ^= 1; }
    inline void down(int p) { if (t[p]) mark(ls), mark(rs), t[p] = 0; }
    inline void upd(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p);
        down(p); Mid; upd(goL, x, y); upd(goR, x, y); up(p);
    }
}
using namespace Seg;

inline void dfs0(int u) {
    w[u] = max(1, sz[u]);
    if (!sz[u]) return;
    for (auto &v : T[u]) dfs0(v), mul(w[u], w[v]);
    pre[0] = 1; For (i, 1, sz[u] - 1) pre[i] = ml(pre[i - 1], w[T[u][i - 1]]);
    suf[sz[u] - 1] = 1; rFor (i, sz[u] - 2, 0) suf[i] = ml(suf[i + 1], w[T[u][i + 1]]);
    For (i, 0, sz[u] - 1) g[T[u][i]] = ml(pre[i], suf[i]);
}

inline void dfs(int u, int x) {
    f[u] = x;
    for (auto &v : T[u]) dfs(v, ml(x, g[v]));
}

void init(int N, int M, vector<int > P, vector<int > A) {
    n = N, m = M;
    For (i, 1, n + m - 1) T[P[i]].pb(i);
    For (i, 0, n + m - 1) sz[i] = T[i].size();
    dfs0(0); dfs(0, 1);
    build(1, n, n + m - 1);
    For (i, 0, m - 1) if (A[i]) upd(1, n, n + m - 1, n + i, n + i);
}

int count_ways(int L, int R) {
    upd(1, n, n + m - 1, L, R);
    return s[1];
}