#include<bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5, inf = 1e9;
inline void cmin(int &x, const int &y) { y<x? x=y: 0; }

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

int T, n, m;

namespace Seg {
    int o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = min(o[ls], o[rs]); }
    inline void upd(int p, int l, int r, int x, const int &v) {
        if (l > x || r < x) return;
        if (l == r) return cmin(o[p], v);
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline int query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return inf;
        if (x <= l && r <= y) return o[p];
        M; return min(query(goL, x, y), query(goR, x, y));
    }
}
using namespace Seg;

int main() {
    io >> T;
    while (T--) {
        memset(o, 31, sizeof o);
        io >> n >> m;
        upd(1, 1, n, 1, 0);
        int l, r;
        while (m--) io >> l >> r, upd(1, 1, n, r, query(1, 1, n, l, r) + 1);
        printf("%d\n", query(1, 1, n, n, n));
        if (T) puts("");
    }

    return 0;
}
