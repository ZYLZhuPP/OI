#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e4 + 5, M = 105;

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

int n, K;
int d[N], c[N], s[N], w[N], f[M][N], ans;

struct LR {
    int l, r, c;
    bool operator < (const LR &x) const { return r < x.r; }
} lr[N];

namespace Seg {
    int o[N << 2], t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    void up(int p) { o[p] = min(o[ls], o[rs]); }
    void mark(int p, int d) { o[p] += d; t[p] += d; }
    void down(int p) { if (t[p]) mark(ls, t[p]), mark(rs, t[p]), t[p] = 0; }
    void build(int p, int l, int r) { o[p] = INT_MAX; t[p] = 0; if (l < r) { M; build(goL); build(goR); } }
    int query() { return o[1]; }
    void upd(int p, int l, int r, int x, int y, int d) {
        if (r < x || l > y) return;
        if (x <= l && r <= y) return mark(p, d);
        down(p); M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    void upd(int p, int l, int r, int x, int v) {
        if (l > x || r < x) return;
        if (l == r) return void(o[p] = v);
        down(p); M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
}

int main() {
    io >> n >> K;
    For (i, 2, n) io >> d[i];
    For (i, 1, n) io >> c[i];
    For (i, 1, n) io >> s[i];
    For (i, 1, n) io >> w[i];
    For (i, 1, n) {
        lr[i].l = lower_bound(d + 1, d + i + 1, d[i] - s[i]) - d;
        lr[i].r = upper_bound(d + i, d + n + 1, d[i] + s[i]) - d - 1;
        lr[i].c = w[i];
    }
    sort(lr + 1, lr + n + 1);

    For (i, 1, n) ans += w[i];
    if (!K) { printf("%d", ans); return 0; }

    int p = 1, cost = 0;
    For (i, 1, n) {
        f[1][i] = cost + c[i];
        while (p <= n && lr[p].r <= i)
            cost += lr[p].c, p++;
    }

    For (k, 1, K) {
        Seg::build(1, 1, n);
        p = 1;
        For (i, 1, n) {
            f[k + 1][i] = (i > 1? Seg::query(): 0) + c[i];
            while (p <= n && lr[p].r <= i) {
                if (lr[p].l > 1) Seg::upd(1, 1, n, 1, lr[p].l - 1, lr[p].c);
                p++;
            }
            Seg::upd(1, 1, n, i, f[k][i]);
        }
        ans = min(ans, Seg::query());
    }
    printf("%d", ans);
    
    return 0;
}