#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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

int T, n, q, pos;
ll S, a[N], f[N], g[N];

namespace Seg {
    ll mx[N << 2], t1[N << 2], t2[N << 2], s1[N << 2], s2[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void up(int p) { mx[p] = max(mx[ls], mx[rs]); }
    inline void Up1(int p) { s1[p] = s1[ls] + s1[rs]; }
    inline void Up2(int p) { s2[p] = s2[ls] + s2[rs]; }
    inline void mark1(int p, int l, int r, ll v) { s1[p] = (r - l + 1) * v; t1[p] = v; }
    inline void mark2(int p, int l, int r, ll v) { s2[p] = (r - l + 1) * v; t2[p] = v; }
    inline void down1(int p, int l, int r) { M; if (t1[p]) mark1(goL, t1[p]), mark1(goR, t1[p]), t1[p] = 0; }
    inline void down2(int p, int l, int r) { M; if (t2[p]) mark2(goL, t2[p]), mark2(goR, t2[p]), t2[p] = 0; }
    inline void build(int p, int l, int r) {
        t1[p] = t2[p] = 0;
        if (l == r) return mx[p] = a[l], s1[p] = f[l], s2[p] = g[l], void();
        M; build(goL); build(goR); up(p); Up1(p); Up2(p);
    }
    inline void upd(int p, int l, int r, int x) {
        if (l == r) return mx[p] = a[x], void();
        M; x<=m? upd(goL, x): upd(goR, x); up(p);
    }
    inline void Upd1(int p, int l, int r, int x, int y, ll v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark1(I, v);
        down1(I); M; Upd1(goL, x, y, v); Upd1(goR, x, y, v); Up1(p);
    }
    inline void Upd2(int p, int l, int r, int x, int y, ll v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark2(I, v);
        down2(I); M; Upd2(goL, x, y, v); Upd2(goR, x, y, v); Up2(p);
    }
    inline int findL(int p, int l, int r, ll v) {
        if (l == r) return l;
        M; return mx[ls]>=v? findL(goL, v): findL(goR, v);
    }
    inline int findR(int p, int l, int r, ll v) {
        if (l == r) return l;
        M; return mx[rs]>=v? findR(goR, v): findR(goL, v);
    }
}
using namespace Seg;

int main() {
    io >> T;
    while (T--) {
        pos = S = 0;
        io >> n;
        For (i, 1, n) io >> a[i], f[i] = max(f[i - 1], a[i]), S += a[i];
        g[n + 1] = 0; rFor (i, n, 1) g[i] = max(g[i + 1], a[i]);
        For (i, 1, n) if (a[i] > a[pos]) pos = i;
        build(1, 1, n);
        io >> q;
        while (q--) {
            int x, d;
            io >> x >> d; S += d;
            ll y = a[x] + d;
            if (y > a[pos]) pos = x, Upd1(1, 1, n, x, n, y), Upd2(1, 1, n, 1, x, y);
            else {
                if (pos < x) {
                    int z = findR(1, 1, n, y);
                    if (z < x) Upd2(1, 1, n, z + 1, x, y);
                } else {
                    int z = findL(1, 1, n, y);
                    if (z > x) Upd1(1, 1, n, x, z - 1, y);
                }
            }
            a[x] = y;
            upd(1, 1, n, x);
            printf("%lld\n", s1[1] + s2[1] - n * a[pos] - S);
        }
    }

    return 0;
}
