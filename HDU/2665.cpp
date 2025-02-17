#include<bits/stdc++.h>
using namespace std;

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

int T, n, m, a[N], b[N], B;

namespace Seg {
    struct Node { int l, r, sz; } o[N * 25];
    int rt[N], tot;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline int copy(int p) { o[++tot] = o[p]; return tot; }
    inline void upd(int &p, int l, int r, int x) {
        if (l > x || r < x) return;
        p = copy(p); o[p].sz++;
        if (l == r) return;
        M; upd(goL, x); upd(goR, x);
    }
    inline int count(int p, int l, int r, int q, int x, int y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y ) return o[q].sz - o[p].sz;
        M; return count(goL, o[q].l, x, y) + count(goR, o[q].r, x, y);
    }
    int kth(int p, int l, int r, int q, int k) {
        if (l == r) return l;
        int x = o[o[q].l].sz - o[ls].sz;
        M; return k<=x? kth(goL, o[q].l, k): kth(goR, o[q].r, k - x);
    }
}
using namespace Seg;

int main() {
    io >> T;
    while (T--) {
        tot = 0;
        io >> n >> m;
        int l, r, k;
        For (i, 1, n) io >> a[i], b[i] = a[i];
        sort(b + 1, b + n + 1); B = unique(b + 1, b + n + 1) - b - 1;
        For (i, 1, n) a[i] = lower_bound(b + 1, b + B + 1, a[i]) - b, upd(rt[i] = rt[i - 1], 1, n, a[i]);
        while (m--) {
            io >> l >> r >> k;
            printf("%d\n", b[kth(rt[l - 1], 1, n, rt[r], k)]);
        }
    }

    return 0;
}