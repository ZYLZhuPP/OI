#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, M = 3e5 + 5, inf = 1e9;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, a[N], m, ans[M];
vector<array<int, 2 > > op[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int v) { for (; x; x -= lowbit(x)) cmin(o[x], v); }
    inline int query(int x) { int r = inf; for (; x < N; x += lowbit(x)) cmin(r, o[x]); return r; }
}

namespace Seg {
    struct Node { int l, r, mx; } o[N << 6];
    int tot, rt;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(int &p, int l, int r, int x, int v) {
        if (l > x || r < x) return;
        if (!p) p = ++tot;
        cmax(o[p].mx, v);
        if (l == r) return;
        M; upd(goL, x, v); upd(goR, x, v);
    }
    inline int query(int p, int l, int r, int x, int y) {
        if (!p || l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p].mx;
        M; return max(query(goL, x, y), query(goR, x, y));
    }
}
using namespace Seg;


inline void solve() {
    memset(BIT::o, 63, sizeof BIT::o);
    For (i, 1, tot) o[i] = {0, 0, 0};
    tot = rt = 0;
    For (i, 1, n) {
        int pos = query(rt, 0, inf, a[i], inf);
        while (pos) {
            BIT::upd(pos, a[pos] - a[i]);
            pos = query(rt, 0, inf, a[i], (a[i] + a[pos] - 1) / 2);
        }
        upd(rt, 0, inf, a[i], i);
        for (auto &[l, id] : op[i]) cmin(ans[id], BIT::query(l));
    }
}

int main() {
    memset(ans, 63, sizeof ans);
    io >> n;
    For (i, 1, n) io >> a[i];
    io >> m;
    int l, r;
    For (i, 1, m) io >> l >> r, op[r].pb({l, i});
    solve();
    For (i, 1, n) a[i] = inf - a[i];
    solve();
    For (i, 1, m) printf("%d\n", ans[i]);

    return 0;
}
