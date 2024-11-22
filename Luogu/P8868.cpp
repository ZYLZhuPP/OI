#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
const int N = 3e5 + 5;

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
    struct D {
        ull xy, x, y, s;
        D(ull xy = 0, ull x = 0, ull y = 0, ull s = 0): xy(xy), x(x), y(y), s(s) { }
        D operator + (const D &a) const { return {xy + a.xy, x + a.x, y + a.y, s + a.s}; }
    } o[N << 2];
    struct T {
        ull tx, ty, xy, x, y, c;
        T(ull tx = 0, ull ty = 0, ull xy = 0, ull x = 0, ull y = 0, ull c = 0): tx(tx), ty(ty), xy(xy), x(x), y(y), c(c) { }
        T& operator += (const T &a) {
            if (tx && ty) c += a.xy * tx * ty + a.x * tx + a.y * ty + a.c;
            else if (tx) y += a.xy * tx + a.y, c += a.x * tx + a.c;
            else if (ty) x += a.xy * ty + a.x, c += a.y * ty + a.c;
            else xy += a.xy, x += a.x, y += a.y, c += a.c;
            if (a.tx) tx = a.tx;
            if (a.ty) ty = a.ty;
            return *this;
        }
    } t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void up(int p) { o[p] = o[ls] + o[rs]; }
    inline void mark(int p, int l, int r, const T &d) {
        ull len = r - l + 1;
        o[p].s += d.xy * o[p].xy + d.x * o[p].x + d.y * o[p].y + len * d.c;
        if (d.tx && d.ty) {
            o[p].xy = len * d.tx * d.ty;
            o[p].x = len * d.tx; o[p].y = len * d.ty;
        } else if (d.tx) {
            o[p].xy = o[p].y * d.tx;
            o[p].x = len * d.tx;
        } else if (d.ty) {
            o[p].xy = o[p].x * d.ty;
            o[p].y = len * d.ty;
        }
        t[p] += d;
    }
    inline void down(int p, int l, int r) { M; mark(goL, t[p]); mark(goR, t[p]); t[p] = T(); }
    inline void upd(int p, int l, int r, int x, int y, const T &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(I, d);
        down(I); M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline ull query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p].s;
        down(I); M; return query(goL, x, y) + query(goR, x, y);
    }
}
using namespace Seg;

int ID, n, q, a[N], b[N], A[N], B[N], tA, tB;
ull ans[N];
vector<array<int, 2 > > qs[N];

int main() {
    io >> ID >> n;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) io >> b[i];
    io >> q;
    int l, r;
    For (i, 1, q) io >> l >> r, qs[r].pb({l, i});
    For (i, 1, n) {
        while (tA && a[A[tA]] < a[i]) tA--;
        upd(1, 1, n, A[tA] + 1, i, T(a[i]));
        A[++tA] = i;
        while (tB && b[B[tB]] < b[i]) tB--;
        upd(1, 1, n, B[tB] + 1, i, T(0, b[i]));
        B[++tB] = i;
        upd(1, 1, n, 1, n, T(0, 0, 1));
        for (auto &[l, id] : qs[i]) ans[id] = query(1, 1, n, l, i);
    }
    For (i, 1, q) printf("%llu\n", ans[i]);

    return 0;
}
