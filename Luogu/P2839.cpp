#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e4 + 5, inf = 1e9;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () { return ~c; }
} io;

int Q, n, a[N], b[N], B, ans, q[4];
vector<int > pt[N];

namespace Seg {
    struct Node { int l, r, mn, mx, t; } o[N * 60];
    int tot, rt[N];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].mn = min(o[ls].mn, o[rs].mn) + o[p].t; o[p].mx = max(o[ls].mx, o[rs].mx) + o[p].t; }
    inline int copy(int p) { o[++tot] = o[p]; return tot; }
    inline void mark(int p, const int &d) { o[p].t += d; o[p].mn += d; o[p].mx += d; }
    inline void build(int &p, int l, int r) {
        p = ++tot;
        if (l == r) return void(o[p].mn = o[p].mx = l);
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int &p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        p = copy(p);
        if (x <= l && r <= y) return mark(p, d);
        M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline int query_mn(int &p, int l, int r, int x, int y) {
        if (l > y || r < x) return inf;
        if (x <= l && r <= y) return o[p].mn;
        M; return min(query_mn(goL, x, y), query_mn(goR, x, y)) + o[p].t;
    }
    inline int query_mx(int &p, int l, int r, int x, int y) {
        if (l > y || r < x) return -inf;
        if (x <= l && r <= y) return o[p].mx;
        M; return max(query_mx(goL, x, y), query_mx(goR, x, y)) + o[p].t;
    }
}
using namespace Seg;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1); B = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, n) a[i] = lower_bound(b + 1, b + B + 1, a[i]) - b, pt[a[i]].pb(i);
    build(rt[1], 0, n);
    For (i, 2, B) {
        rt[i] = rt[i - 1];
        for (auto &x : pt[i - 1]) upd(rt[i], 0, n, x, n, -2);
    }
    io >> Q;
    while (Q--) {
        For (i, 0, 3) io >> q[i], q[i] = (q[i] + ans) % n + 1;
        sort(q, q + 4);
        int l = ans = 1, r = B;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (query_mx(rt[mid], 0, n, q[2], q[3]) - query_mn(rt[mid], 0, n, q[0] - 1, q[1] - 1) >= 0) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        printf("%d\n", ans = b[ans]);
    }

    return 0;
}
