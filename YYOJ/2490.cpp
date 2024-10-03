#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int n, q, a[N], b[N], B, x[N], p[N];
set<int > pos[N];

namespace Seg {
    int o[N << 2], t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = max(o[ls], o[rs]) + t[p]; }
    inline void Upd(int p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return o[p] += d, t[p] += d, void();
        M; Upd(goL, x, y, d); Upd(goR, x, y, d); up(p);
    }
    inline void upd(int p, int l, int r, int x) {
        if (l > x || r < x) return;
        if (l == r) return void(o[p] = *pos[x].rbegin() + t[p]);
        M; upd(goL, x); upd(goR, x); up(p);
    }
}
using namespace Seg;

int main() {
    io >> n >> q;
    For (i, 1, n) io >> a[i], b[++B] = a[i];
    For (i, 1, q) io >> p[i] >> x[i], b[++B] = x[i];
    sort(b + 1, b + B + 1); B = unique(b + 1, b + B + 1) - b - 1;
    For (i, 1, B) pos[i].insert(0);
    For (i, 1, n) a[i] = lower_bound(b + 1, b + B + 1, a[i]) - b;
    For (i, 1, q) x[i] = lower_bound(b + 1, b + B + 1, x[i]) - b;
    For (i, 1, n) {
        Upd(1, 1, B, 1, a[i] - 1, 1);
        pos[a[i]].insert(i);
        upd(1, 1, B, a[i]);
    }
    For (i, 1, q) {
        Upd(1, 1, B, 1, a[p[i]] - 1, -1);
        pos[a[p[i]]].erase(p[i]);
        upd(1, 1, B, a[p[i]]);
        a[p[i]] = x[i];
        Upd(1, 1, B, 1, a[p[i]] - 1, 1);
        pos[a[p[i]]].insert(p[i]);
        upd(1, 1, B, a[p[i]]);
        printf("%d\n", o[1] - n + 1);
    }

    return 0;
}
