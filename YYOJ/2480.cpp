#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2.5e5 + 5, inf = 1e9;

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

int n;

namespace Seg {
    multiset<int > se[N << 3][2];
    int o[N << 3], f[N << 3][2], g[N << 3][2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) {
        o[p] = min(min(o[ls], o[rs]), min(f[ls][0] + g[rs][1], f[ls][1] + g[rs][0]));
        For (k, 0, 1) f[p][k] = min(f[ls][k], f[rs][k]), g[p][k] = min(g[ls][k], g[rs][k]);
    }
    inline void build(int p, int l, int r) {
        if (l == r) {
            o[p] = inf;
            For (k, 0, 1) se[p][k].insert(f[p][k] = g[p][k] = inf);
            return;
        }
        M; build(goL); build(goR); up(p);
    }
    inline void ins(int p, int l, int r, int k, int x, int y) {
        if (l > x || r < x) return;
        if (l == r) {
            se[p][k].insert(y);
            f[p][k] = *se[p][k].begin();
            g[p][k] = f[p][k] + x;
            o[p] = min(inf, f[p][0] + g[p][1]);
            return;
        }
        M; ins(goL, k, x, y); ins(goR, k, x, y); up(p);
    }
    inline void del(int p, int l, int r, int k, int x, int y) {
        if (l > x || r < x) return;
        if (l == r) {
            se[p][k].erase(se[p][k].find(y));
            f[p][k] = *se[p][k].begin();
            g[p][k] = min(inf, f[p][k] + x);
            o[p] = min(inf, f[p][0] + g[p][1]);
            return;
        }
        M; del(goL, k, x, y); del(goR, k, x, y); up(p);
    }
}
using namespace Seg;

int main() {
    io >> n;
    build(1, -N, N);
    int op, k, x, y;
    while (n--) {
        io >> op >> k >> x >> y; k--;
        if (op == 1) !k? ins(1, -N, N, 0, x - y, y): ins(1, -N, N, 1, y - x, x);
        else !k? del(1, -N, N, 0, x - y, y): del(1, -N, N, 1, y - x, x);
        printf("%d\n", o[1]<inf? o[1]: -1);
    }

    return 0;
}
