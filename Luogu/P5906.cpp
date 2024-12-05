#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
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

int n, m, q, B, a[N], b[N], mn[N], mx[N], ans[N], res;
vector<array<int, 3 > > qs[505];
vector<array<int, 4 > > stk;

inline void add(int i, int k) {
    int x = a[i];
    if (k) stk.pb({x, mx[x], mn[x], res});
    cmax(mx[x], i); cmin(mn[x], i);
    cmax(res, mx[x] - mn[x]);
}

inline void back() {
    while (!stk.empty()) {
        auto [x, a, b, c] = stk.back(); stk.pop_back();
        mx[x] = a, mn[x] = b, res = c;
    }
}

int main() {
    io >> n; B = sqrt(n);
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1); m = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, m) mn[i] = n + 1;
    For (i, 1, n) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
    io >> q;
    int l, r;
    For (i, 1, q) io >> l >> r, qs[(l - 1) / B].pb({r, l, i});
    For (i, 0, B + 1) {
        res = 0;
        For (j, 1, m) mn[j] = n + 1, mx[j] = 0;
        sort(qs[i].begin(), qs[i].end());
        int l = (i + 1) * B, r = l;
        for (auto &[y, x, id] : qs[i]) {
            if (y <= l) {
                For (j, x, y) add(j, 1);
                ans[id] = res; back();
                continue;
            }
            while (r < y) add(++r, 0);
            rFor (j, l, x) add(j, 1);
            ans[id] = res; back();
        }
    }
    For (i, 1, q) printf("%d\n", ans[i]);

    return 0;
}
