#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int n, m, B, a[N], pt[N], dfn[N], tim, tot, st[N][17], Ans[N];
int Pre[N], Suf[N], Cnt[N], pre[N], suf[N], cnt[N], ans;
vector<array<int, 3 > > qs[N];
vector<int > T[N];

inline void dfs0(int u) {
    pt[++tim] = u; st[dfn[u] = ++tot][0] = u;
    for (auto &v : T[u]) dfs0(v), st[++tot][0] = u;
}

inline int dmin(int x, int y) { return dfn[x]<dfn[y]? x: y; }

inline int lca(int u, int v) {
    int l = dfn[u], r = dfn[v]; if (l > r) swap(l, r);
    int k = 31 - __builtin_clz(r - l + 1);
    return dmin(st[l][k], st[r - (1 << k) + 1][k]);
}

inline void init() {
    For (j, 1, 16) For (i, 1, tot - (1 << j) + 1) st[i][j] = dmin(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    For (i, 1, n) Pre[pt[i]] = pt[i - 1], Suf[pt[i]] = pt[i + 1], Cnt[i] = 1;
    For (i, 1, n - 1) Cnt[lca(pt[i], pt[i + 1])]++;
}

inline void del(int x) { if (!--cnt[x]) ans--; }
inline void ins(int x) { if (!cnt[x]++) ans++; }

inline void Del(int x) {
    int l = pre[x], r = suf[x];
    del(x);
    if (l) suf[l] = r, del(lca(l, x));
    if (r) pre[r] = l, del(lca(r, x));
    if (l && r) ins(lca(l, r));
}

inline void Ins(int x) {
    int l = pre[x], r = suf[x];
    ins(x);
    if (l) suf[l] = x, ins(lca(l, x));
    if (r) pre[r] = x, ins(lca(r, x));
    if (l && r) del(lca(l, r));
}

inline void build(int x) {
    ans = n;
    For (i, 1, n) pre[i] = Pre[i], suf[i] = Suf[i], cnt[i] = Cnt[i];
    For (i, 1, x - 1) Del(a[i]);
}

int main() {
    io >> n >> m; B = sqrt(n);
    int x;
    For (i, 2, n) io >> x, T[x].pb(i);
    dfs0(1); init();
    For (i, 1, n) io >> a[i];
    int l, r;
    For (i, 1, m) io >> l >> r, qs[(l - 1) / B].pb({-r, l, i});
    For (i, 0, B + 1) if (!qs[i].empty()) {
        sort(qs[i].begin(), qs[i].end());
        int x = i * B + 1, y = n;
        build(x);
        for (auto &[r, l, id] : qs[i]) {
            r = -r;
            while (r < y) Del(a[y--]);
            For (j, x, l - 1) Del(a[j]);
            Ans[id] = ans;
            rFor (j, l - 1, x) Ins(a[j]);
        }
    }
    For (i, 1, m) printf("%d\n", Ans[i]);

    return 0;
}
