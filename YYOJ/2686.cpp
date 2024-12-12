#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 1e9 + 7, inv2 = 5e8 + 4;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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
    int o[N << 2], t[N << 2], on[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { on[p] = on[ls] | on[rs]; o[p] = ml(t[p], mo(on[ls] * o[ls] + on[rs] * o[rs])); }
    inline void build(int p, int l, int r) {
        t[p] = 1; on[p] = o[p] = 0;
        if (l == r) return o[p] = 1, void();
        M; build(goL); build(goR);
    }
    inline void upd(int p, int l, int r, int x, int y, int v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mul(t[p], v), mul(o[p], v);
        M; upd(goL, x, y, v); upd(goR, x, y, v); up(p);
    }
    inline void turn(int p, int l, int r, int x) {
        if (l == r) return on[p] = 1, void();
        M; x<=m? turn(goL, x): turn(goR, x); up(p);
    }
    inline int query(int p, int l, int r, int x, int y, int k = 1) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return ml(k, on[p] * o[p]);
        mul(k, t[p]); M; return mo(query(goL, x, y, k) + query(goR, x, y, k));
    }
}
using namespace Seg;

int n, a[N], _2[N], ans;

inline void solve() {
    build(1, 1, n);
    For (i, 1, n) upd(1, 1, n, 1, a[i] - 1, 2);
    For (i, 1, n) {
        upd(1, 1, n, 1, a[i] - 1, inv2);
        turn(1, 1, n, a[i]);
        add(ans, -query(1, 1, n, a[i], n));
        upd(1, 1, n, a[i] + 1, n, 2);
    }
    build(1, 1, n);
    For (i, 1, n) {
        turn(1, 1, n, a[i]);
        add(ans, query(1, 1, n, a[i], n));
        upd(1, 1, n, a[i] + 1, n, 2);
    }
}

int main() {
    io >> n;
    _2[0] = 1; For (i, 1, n) _2[i] = mo(_2[i - 1] << 1);
    For (i, 1, n) add(ans, ml(_2[i], _2[n - i] - 1));
    int x, y;
    For (i, 1, n) io >> x >> y, a[x] = y;
    solve();
    For (i, 1, n) a[i] = n - a[i] + 1;
    solve();
    printf("%d", mo(ans << 1));

    return 0;
}
