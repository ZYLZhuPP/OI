#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5, M = N * 60;

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

int n, K, a[N], b[N], ls[N], rs[N], f[N];
int rt[N], lc[M], rc[M], tot;
bool flag[M];

inline int cover(int l, int r, int x, int y) {
    if (l > y || r < x) return 0;
    int p = ++tot;
    if (x <= l && r <= y) return flag[p] = 1, p;
    int m = (l + r) >> 1;
    lc[p] = cover(l, m, x, y); rc[p] = cover(m + 1, r, x, y);
    return p;
}

inline int AND(int u, int v) {
    if (!u || !v) return 0;
    if (flag[u]) return v;
    if (flag[v]) return u;
    int p = ++tot;
    lc[p] = AND(lc[u], lc[v]);
    rc[p] = AND(rc[u], rc[v]);
    if (!lc[p] && !rc[p]) return 0;
    flag[p] = flag[lc[p]] & flag[rc[p]];
    return p;
}

inline int OR(int u, int v) {
    if (!u || !v) return u | v;
    if (flag[u]) return u;
    if (flag[v]) return v;
    int p = ++tot;
    lc[p] = OR(lc[u], lc[v]);
    rc[p] = OR(rc[u], rc[v]);
    if (!lc[p] && !rc[p]) return 0;
    flag[p] = flag[lc[p]] & flag[rc[p]];
    return p;
}

inline void dfs(int u) {
    if (!u) return;
    dfs(ls[u]); dfs(rs[u]);
    if (a[u] == b[u]) rt[u] = cover(0, K - 1, 0, K - 1);
    else if (a[u] < b[u]) rt[u] = cover(0, K - 1, K - b[u], K - a[u] - 1);
    else rt[u] = OR(cover(0, K - 1, 0, K - a[u] - 1), cover(0, K - 1, K - b[u], K - 1));
    if (!ls[u] && !rs[u]) return;
    else if (!ls[u] || !rs[u]) {
        int v = ls[u] | rs[u];
        f[u] = f[v];
        int x = AND(rt[u], rt[v]);
        rt[u] = x? x: (f[u]++, OR(rt[u], rt[v]));
    } else {
        int v1 = ls[u], v2 = rs[u];
        f[u] = f[v1] + f[v2];
        int x = AND(rt[u], AND(rt[v1], rt[v2]));
        if (x) rt[u] = x;
        else {
            int y = OR(OR(AND(rt[u], rt[v1]), AND(rt[u], rt[v2])), AND(rt[v1], rt[v2]));
            rt[u] = y? f[u]++, y: (f[u] += 2, OR(rt[u], OR(rt[v1], rt[v2])));
        }
    }
}

int main() {
    io >> n >> K;
    For (i, 1, n) io >> a[i] >> b[i] >> ls[i] >> rs[i];
    dfs(1);
    int x = rt[1];
    while (x && !flag[x]) x = lc[x];
    if (!x) f[1]++;
    printf("%d", f[1]);

    return 0;
}
