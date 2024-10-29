#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5, Mo = 19940417;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, q, a[N], C[N][21];

namespace Seg {
    struct poly {
        int o[21];
        poly(int x = 0) { memset(o, 0, sizeof o); o[0] = x; }
        poly operator * (const poly &a) const {
            poly r;
            For (i, 0, 20) if (a.o[i]) For (j, 0, 20 - i) add(r.o[i + j], ml(a.o[i], o[j]));
            return r;
        }
    } o[N << 2];
    int t[N << 2]; bool v[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void up(int p) { o[p] = o[ls] * o[rs]; }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p].o[0] = 1, o[p].o[1] = mo(a[l] % Mo), void();
        M; build(goL); build(goR); up(p);
    }
    inline void rev(int p) { For (i, 1, 19) if (i & 1) o[p].o[i] = Mo - o[p].o[i]; t[p] = Mo - t[p]; v[p] ^= 1; }
    inline void mark(int p, int l, int r, int d) {
        int _[21];
        _[0] = 1; For (i, 1, 20) _[i] = ml(_[i - 1], d);
        rFor (i, 20, 0) For (j, 0, i - 1) add(o[p].o[i], ml(o[p].o[j], ml(_[i - j], C[r - l + 1 - j][i - j])));
        add(t[p], d);
    }
    inline void down(int p, int l, int r) {
        M;
        if (v[p]) rev(ls), rev(rs), v[p] ^= 1;
        if (t[p]) mark(goL, t[p]), mark(goR, t[p]), t[p] = 0;
    }
    inline void upd(int p, int l, int r, int x, int y, int d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(I, d);
        down(I); M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline void rev(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return rev(p);
        down(I); M; rev(goL, x, y); rev(goR, x, y); up(p);
    }
    inline poly query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return poly(1);
        if (x <= l && r <= y) return o[p];
        down(I); M; return query(goL, x, y) * query(goR, x, y);
    }
}
using namespace Seg;

inline void init() {
    For (i, 0, N - 1) C[i][0] = 1;
    For (i, 1, N - 1) For (j, 1, 20) C[i][j] = mo(C[i - 1][j - 1] + C[i - 1][j]);
}

int main() {
    init();
    io >> n >> q;
    For (i, 1, n) io >> a[i];
    build(1, 1, n);
    char op[3]; int l, r, x;
    while (q--) {
        scanf("%s", op);
        if (op[0] == 'I') io >> l >> r >> x, upd(1, 1, n, l, r, mo(x % Mo));
        else if (op[0] == 'R') io >> l >> r, rev(1, 1, n, l, r);
        else io >> l >> r >> x, printf("%d\n", query(1, 1, n, l, r).o[x]);
    }

    return 0;
}
