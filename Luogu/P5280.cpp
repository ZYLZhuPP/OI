#include<bits/stdc++.h>
using namespace std;

const int Mo = 998244353, inv2 = 499122177;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline void mul(int &x, int y) { x = ml(x, y); }

struct IO {
    int c, f;
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

int n, m, op, S, l, r;

namespace tr {
    const int N = 1 << 18;
    int f[N], g[N], t[N], sf[N];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define me p, l, r
#define goL ls, l, m
#define goR rs, m + 1, r
    void build(int p, int l, int r) {
        t[p] = 1; if (l == r) return;
        M; build(goL); build(goR);
    }
    inline void mark(int p, int x) { g[p] = mo(ml(g[p], x) + 1 - x); mul(t[p], x); }
    inline void down(int p) { mark(ls, t[p]); mark(rs, t[p]); t[p] = 1; }
    inline void up(int p, int l, int r) {
        sf[p] = f[p];
        if (l < r) add(sf[p], mo(sf[ls] + sf[rs]));
    }
    void upd(int p, int l, int r, int x, int y) {
        if (l > y || r < x) {
            f[p] = ml(mo(f[p] + g[p]), inv2);
            return up(me);
        }
        if (x <= l && r <= y) {
            f[p] = ml(f[p] + 1, inv2);
            mark(p, inv2);
            return up(me);
        }
        down(p);
        mul(f[p], inv2); mul(g[p], inv2);
        M; upd(goL, x, y); upd(goR, x, y);
        return up(me);
    }
}

int main() {
    io >> n >> m;
    tr::build(1, 1, n); S = 1;
    while (m--) {
        io >> op;
        if (op == 1) {
            io >> l >> r;
            tr::upd(1, 1, n, l, r);
            add(S, S);
        } else printf("%d\n", ml(S, tr::sf[1]));
    }

    return 0;
}
