#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 12e4 + 5;

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

namespace Seg {
    struct Node {
        int mn, c, t, tag, tagt; ll s;
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].mn = min(o[ls].mn, o[rs].mn); o[p].c = (o[ls].mn==o[p].mn? o[ls].c: 0) + (o[rs].mn==o[p].mn? o[rs].c: 0); o[p].s = o[ls].s + o[rs].s; }
    inline void mark(int p, int d) { o[p].mn += d; o[p].tag += d; }
    inline void markt(int p, int d) { o[p].s += 1ll * d * o[p].c; o[p].tagt += d; }
    inline void down(int p) {
        if (o[p].tag) mark(ls, o[p].tag), mark(rs, o[p].tag), o[p].tag = 0;
        if (o[p].tagt) {
            if (o[ls].mn == o[p].mn) markt(ls, o[p].tagt);
            if (o[rs].mn == o[p].mn) markt(rs, o[p].tagt);
            o[p].tagt = 0;
        } 
    }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p].mn = l, o[p].c = 1, void();
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x, int y, int d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, d);
        down(p); M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline ll query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p].s;
        down(p); M; return query(goL, x, y) + query(goR, x, y);
    }
}
using namespace Seg;

int n, a[N], Q, q1[N], q2[N], t1, t2;
ll ans[N];
vector<array<int, 2 > > q[N];

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    io >> Q;
    int l, r;
    For (i, 1, Q) io >> l >> r, q[r].pb({l, i});
    build(1, 1, n);
    For (i, 1, n) {
        while (t1 && a[i] > a[q1[t1]]) upd(1, 1, n, q1[t1 - 1] + 1, q1[t1], a[i] - a[q1[t1]]), t1--;
        while (t2 && a[i] < a[q2[t2]]) upd(1, 1, n, q2[t2 - 1] + 1, q2[t2], a[q2[t2]] - a[i]), t2--;
        q1[++t1] = q2[++t2] = i;
        markt(1, 1);
        for (auto &[l, id] : q[i]) ans[id] = query(1, 1, n, l, i);
    }
    For (i, 1, Q) printf("%lld\n", ans[i]);

    return 0;
}