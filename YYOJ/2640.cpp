#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, inf = 1e9;

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

const int pri[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int n, m, on[N], d[10];

struct Seg {
    int o[N << 2][2], t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p][0] = min(o[ls][0], o[rs][0]), o[p][1] = min(o[ls][1], o[rs][1]) + t[p]; }
    inline void mark(int p, int d) { o[p][1] += d; t[p] += d; }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p][0] = inf, o[p][1] = t[p] = 0, void();
        M; build(goL); build(goR); up(p);
    }
    inline void rev(int p, int l, int r, int x, int k = 0) {
        if (l == r) {
            if (!on[x]) o[p][1] = o[p][0] - k, o[p][0] = inf;
            else o[p][0] = o[p][1] + k, o[p][1] = inf;
            return;
        }
        k += t[p]; M; x<=m? rev(goL, x, k): rev(goR, x, k); up(p);
    }
    inline void upd(int p, int l, int r, int x, int y, int d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, d);
        M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline int query(int p, int l, int r, int x, int y, int k = 0) {
        if (l > y || r < x) return inf;
        if (x <= l && r <= y) return min(o[p][0], o[p][1] + k);
        k += t[p]; M; return min(query(goL, x, y, k), query(goR, x, y, k));
    }
} tr[10];

int main() {
    io >> n >> m;
    For (i, 1, n) on[i] = 1;
    For (i, 0, 9) tr[i].build(1, 1, n);
    int op, l, r, x;
    while (m--) {
        io >> op;
        if (op == 1) {
            io >> x;
            For (i, 0, 9) tr[i].rev(1, 1, n, x);
            on[x] = !on[x];
        } else if (op == 2) {
            io >> l >> r >> x;
            For (i, 0, 9) while (!(x % pri[i])) d[i]++, x /= pri[i];
            For (i, 0, 9) if (d[i]) tr[i].upd(1, 1, n, l, r, d[i]), d[i] = 0;
        } else {
            io >> l >> r >> x;
            if (x == 1) { puts("YES"); continue; }
            bool flag = 1;
            For (i, 0, 9) while (!(x % pri[i])) d[i]++, x /= pri[i];
            For (i, 0, 9) if (d[i]) if (tr[i].query(1, 1, n, l, r) < d[i]) { flag = 0; break; }
            puts(flag? "YES": "NO");
            if (flag) For (i, 0, 9) if (d[i]) tr[i].upd(1, 1, n, l, r, -d[i]);
            For (i, 0, 9) d[i] = 0;
        }
    }

    return 0;
}
