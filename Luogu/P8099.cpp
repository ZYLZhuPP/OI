#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

int n, K, a[N], b[N], l[N], r[N], d[N];
unordered_map<int, int > cnt;

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x <= n; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}

namespace Seg {
    array<int, 2 > o[N << 2]; int t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = min(o[ls], o[rs]); o[p][0] += t[p]; }
    inline void mark(int p, const int &d) { o[p][0] += d; t[p] += d; }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p] = {d[l], l}, void();
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, d);
        M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
}
using namespace Seg;

int main() {
    io >> n >> K;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1);
    For (i, 1, n) {
        cnt[a[i]]++;
        int x = lower_bound(b + 1, b + n + 1, a[i]) - b + cnt[a[i]] - 1;
        l[x] = lower_bound(b + 1, b + n + 1, a[i] - K) - b;
        r[x] = upper_bound(b + 1, b + n + 1, a[i] + K) - b - 1;
        d[x] = i - 1 - BIT::query(r[x]) + BIT::query(l[x] - 1);
        BIT::upd(x, 1);
    }
    build(1, 1, n);
    For (i, 1, n) {
        int x = o[1][1];
        printf("%d\n", b[x]);
        upd(1, 1, n, 1, l[x] - 1, -1);
        upd(1, 1, n, r[x] + 1, n, -1);
        upd(1, 1, n, x, x, n);
    }

    return 0;
}
