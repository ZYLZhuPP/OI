#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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
    inline bool operator ~ () { return ~c; }
} io;

int n, q, L[N], R[N];
ll ans;

namespace Seg {
    struct Node { int l, r, t; ll s; } o[N << 2];
    Node merge(const Node &a, const Node &b, const int &x) {
        if (!~a.t || !~b.t || L[x] > R[x + 1] || R[x] < L[x + 1]) return Node{0, 0, -1, 0};
        if (!a.t && !b.t) return max(a.l, b.l)<=min(a.r, b.r)? Node{max(a.l, b.l), min(a.r, b.r), 0, 0}: (a.l<b.l? Node{a.r, b.l, 1, b.l - a.r}: Node{a.l, b.r, 1, a.l - b.r});
        if (!a.t && b.t) return a.l>b.l? Node{a.l, b.r, 1, b.s + a.l - b.l}: (a.r<b.l? Node{a.r, b.r, 1, b.s + b.l - a.r}: b);
        if (a.t && !b.t) return b.l>a.r? Node{a.l, b.l, 1, a.s + b.l - a.r}: (b.r<a.r? Node{a.l, b.r, 1, a.s + a.r - b.r}: a);
        return Node{a.l, b.r, 1, a.s + b.s + abs(a.r - b.l)};
    }
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define P p, l, r
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p, int l, int r) { M; o[p] = merge(o[ls], o[rs], m); }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p] = Node{L[l], R[l], 0, 0}, void();
        M; build(goL); build(goR); up(P);
    }
    inline void upd(int p, int l, int r, const int &x) {
        if (l > x || r < x) return;
        if (l == r) return o[p] = Node{L[x], R[x], 0, 0}, void();
        M; upd(goL, x); upd(goR, x); up(P);
    }
    inline Node query(int p, int l, int r, const int &x, const int &y) {
        if (x <= l && r <= y) return o[p];
        M; return x<=m? y>m? merge(query(goL, x, y), query(goR, x, y), m): query(goL, x, y): query(goR, x, y);
    }
}
using namespace Seg;

int main() {
    io >> n;
    For (i, 1, n) io >> L[i] >> R[i];
    build(1, 1, n);
    io >> q;
    int sx, sy, tx, ty;
    while (q--) {
        ans = 0;
        io >> sx >> sy >> tx >> ty;
        if (sx > tx) swap(sx, tx), swap(sy, ty);
        Node ans = query(1, 1, n, sx, tx);
        if (sy < L[sx] || sy > R[sx] || ty < L[tx] || ty > R[tx] || !~ans.t) { puts("-1"); continue; }
        printf("%lld\n", tx - sx + (ans.t? ans.s + abs(ans.l - sy) + abs(ans.r - ty): (sy<ans.l? ans.l - sy + abs(ty - ans.l): (sy>ans.r? sy - ans.r + abs(ty - ans.r): abs(sy - ty)))));
    }

    return 0;
}