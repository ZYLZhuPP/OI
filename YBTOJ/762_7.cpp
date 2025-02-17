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

int n, m, a[N], pos[N];
long long ans;

#define lowbit(x) ((x) & -(x))
namespace Bit {
    int o[N];
    inline void upd(int x) { for (; x <= n; x += lowbit(x)) o[x]++; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace Bit;

namespace Seg {
    int tot;
    struct Node {
        int l, r, sz;
        Node() { l = r = sz = 0; }
    } o[N * 200];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].sz = o[ls].sz + o[rs].sz; }
    inline void upd(int &p, int l, int r, const int &x, const int &d) {
        if (l > x || r < x) return;
        if (!p) p = ++tot;
        if (l == r) return void(o[p].sz += d);
        M; upd(goL, x, d); upd(goR, x, d); up(p);
    }
    inline int query(int p, int l, int r, const int &x, const int &y) {
        if (!p || l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p].sz;
        M; return query(goL, x, y) + query(goR, x, y);
    }
}
using namespace Seg;

namespace BIT {
    int rt[N];
    inline void upd(int k, const int &x, const int &d) {
        for (; k <= n; k += lowbit(k)) Seg::upd(rt[k], 1, n, x, d);
    }
    inline int pre(int k, const int &x, const int &y) {
        int r = 0;
        for (; k; k -= lowbit(k)) r += Seg::query(rt[k], 1, n, x, y);
        return r;
    }
    inline int query(const int &l, const int &r, const int &x, const int &y) {
        return pre(r, x, y) - pre(l - 1, x, y);
    }
}
using namespace BIT;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], pos[a[i]] = i, upd(i, a[i], 1);
    rFor (i, n, 1) ans += query(a[i]), upd(a[i]);
    while (m--) {
        printf("%lld\n", ans);
        int x;
        io >> x;
        ans -= query(1, pos[x] - 1, x + 1, n) + query(pos[x] + 1, n, 1, x - 1);
        upd(pos[x], x, -1);
    }

    return 0;
}
