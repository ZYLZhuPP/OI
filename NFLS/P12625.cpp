#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e5 + 5;

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

int n, T, typ, a[N], q[N], top, dep[N], ans;

namespace Seg {
    struct Node {
        int mx, mn, ans;
        Node operator + (const Node &a) const { return {max(mx, a.mx), min(mn, a.mn), max({ans, a.ans, mx - a.mn})}; }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] + o[rs]; }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p] = {dep[l], dep[l], 0}, void();
        M; build(goL); build(goR); up(p);
    }
    inline Node query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return {0, n + 1, 0};
        if (x <= l && r <= y) return o[p];
        M; return query(goL, x, y) + query(goR, x, y);
    }
}
using namespace Seg;

int main() {
    freopen("ds.in", "r", stdin);
    freopen("ds.out", "w", stdout);
    io >> n >> T >> typ;
    For (i, 1, n) io >> a[i];
    q[0] = n + 1;
    rFor (i, n, 1) {
        while (top && a[i] >= a[q[top]]) top--;
        dep[i] = dep[q[top]] + 1;
        q[++top] = i;
    }
    build(1, 1, n);
    int l, r;
    while (T--) {
        io >> l >> r;
        l = (l + ans * typ + n - 1) % n + 1;
        r = (r + ans * typ + n - 1) % n + 1;
        if (l > r) swap(l, r);
        ans = query(1, 1, n, l, r).ans + 1;
        printf("%d\n", ans);
    }

    fclose(stdin); fclose(stdout);
    return 0;
}
