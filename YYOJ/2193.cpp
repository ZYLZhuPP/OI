#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

namespace Seg {
    struct Node {
        int s, ad, mu;
        Node() { s = ad = 0; mu = 1; }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void up(int p) { o[p].s = mo(o[ls].s + o[rs].s); }
    inline void mark(int p, int l, int r, const int &x, const int &d) { mul(o[p].s, x); mul(o[p].mu, x); mul(o[p].ad, x); add(o[p].s, ml(r - l + 1, d)); add(o[p].ad, d); }
    inline void down(int p, int l, int r) { M; if (o[p].ad || o[p].mu ^ 1) mark(goL, o[p].mu, o[p].ad), mark(goR, o[p].mu, o[p].ad), o[p].ad = 0, o[p].mu = 1; }
    inline void upd(int p, int l, int r, int x, int y, const int &mu, const int &ad) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(I, mu, ad);
        down(I); M; upd(goL, x, y, mu, ad); upd(goR, x, y, mu, ad); up(p);
    }
    inline int query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p].s;
        down(I); M; return mo(query(goL, x, y) + query(goR, x, y));
    }
}
using namespace Seg;

int n, m, a[N], vis[N], pt[N], t, ans = 1;
array<int, 2 > b[N];
vector<int > es[N];

inline int dfs(int u, int pre) {
    vis[u] = 1; pt[++t] = u;
    for (auto &v : es[u]) if (v ^ pre) {
        if (vis[v]) return 0;
        return dfs(v, u);
    }
    return u;
}

inline void get(int u, int pre) {
    vis[u] = 1; pt[++t] = u;
    for (auto &v : es[u]) if (v ^ pre) get(v, u);
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], b[i] = {a[i], i};
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
    sort(b + 1, b + n + 1);
    For (i, 1, n) if (!vis[b[i][1]]) {
        t = 0;
        int res = 0, x = dfs(b[i][1], 0);
        if (x) t = 0, get(x, 0);
        upd(1, 1, N, 1, N, 0, 0);
        upd(1, 1, N, 1, a[pt[1]], 1, 1);
        For (i, 2, t) {
            int s = o[1].s;
            if (!x && i > 2) add(res, ((t-i)&1? 1: -1) * s);
            upd(1, 1, N, a[pt[i]] + 1, N, 0, 0);
            upd(1, 1, N, 1, min(a[pt[i]], a[pt[i - 1]]), -1, 0);
            upd(1, 1, N, 1, a[pt[i]], 1, s);
        }
        add(res, o[1].s);
        mul(ans, res);
    }
    printf("%d", ans);

    return 0;
}
