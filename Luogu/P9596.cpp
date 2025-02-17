#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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
    struct Node { int t, mx; } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].mx = max(o[ls].mx, o[rs].mx) + o[p].t; }
    inline void mark(int p, const int &d) { o[p].t += d; o[p].mx += d; }
    inline void upd(int p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, d);
        M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
}
using namespace Seg;

int n, Q, B, x[N];
ll a[N], b[N];

int main() {
    io >> n >> Q;
    For (i, 1, n) io >> a[i], a[i] = 1ll * a[i] * n + i - 1, b[i] = a[i];
    For (i, n + 1, n + Q) io >> x[i] >> a[i], x[i]++, a[i] = 1ll * a[i] * n + x[i] - 1, b[i] = a[i];
    sort(b + 1, b + n + Q + 1); B = unique(b + 1, b + n + Q + 1) - b - 1;
    For (i, 1, n + Q) a[i] = lower_bound(b + 1, b + B + 1, a[i]) - b;
    For (i, 1, n) upd(1, 1, B, a[i], a[i], i), upd(1, 1, B, a[i] + 1, B, -1);
    For (i, n + 1, n + Q) {
        upd(1, 1, B, a[x[i]], a[x[i]], -x[i]), upd(1, 1, B, a[x[i]] + 1, B, 1);
        a[x[i]] = a[i];
        upd(1, 1, B, a[i], a[i], x[i]), upd(1, 1, B, a[i] + 1, B, -1);
        printf("%d\n", o[1].mx - 1);
    }

    return 0;
}