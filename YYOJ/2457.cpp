#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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

int n, q;

namespace Seg {
    int o[N << 2], t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = min(o[ls], o[rs]) + t[p]; }
    inline void mark(int p, const int &d) { o[p] += d; t[p] += d; }
    inline void upd(int p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, d);
        M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline int query(int p, int l, int r, int x, int d) {
        if (l >= x || o[p] + d > 0) return -1;
        if (l == r) return l;
        d += t[p]; M;
        int res = query(goR, x, d);
        return ~res? res: query(goL, x, d);
    }
}
using namespace Seg;

int main() {
    io >> n >> q;
    while (q--) {
        int op, x, y;
        io >> op;
        if (op == 1) {
            io >> x >> y;
            if (x > y) upd(1, 0, n, y, x - 1, 1);
        } else if (op == 2) {
            io >> x >> y;
            if (x > y) upd(1, 0, n, y, x - 1, -1);
        } else if (op == 3) io >> x, printf("%d\n", n - query(1, 0, n, x, 0));
    }

    return 0;
}
