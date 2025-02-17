#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e18;
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

int n, m, a[N];

namespace Seg {
    struct Node {
        ll Mn, mn, cmn, tmn, Mx, mx, cmx, tmx, t, s;
        Node() { tmn = INF; tmx = -INF; t = s = 0; }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void up(int p) {
        Node L = o[ls], R = o[rs];
        o[p].s = L.s + R.s;
        if (L.Mn == R.Mn) o[p].Mn = L.Mn, o[p].cmn = L.cmn + R.cmn, o[p].mn = min(L.mn, R.mn);
        else { if (L.Mn > R.Mn) swap(L, R); o[p].Mn = L.Mn, o[p].cmn = L.cmn, o[p].mn = min(L.mn, R.Mn); }
        if (L.Mx == R.Mx) o[p].Mx = L.Mx, o[p].cmx = L.cmx + R.cmx, o[p].mx = max(L.mx, R.mx);
        else { if (L.Mx < R.Mx) swap(L, R); o[p].Mx = L.Mx, o[p].cmx = L.cmx, o[p].mx = max(L.mx, R.Mx); }
    }
    inline void mark(int p, int l, int r, const int &d) {
        o[p].s += (r - l + 1ll) * d; o[p].t += d; o[p].Mn += d; o[p].Mx += d;
        if (o[p].mn < INF) o[p].mn += d; if (o[p].mx > -INF) o[p].mx += d;
        if (o[p].tmn < INF) o[p].tmn += d; if (o[p].tmx > -INF) o[p].tmx += d;
    }
    inline void mark_mn(int p, const int &mn) {
        if (mn >= o[p].Mx) return;
        o[p].s -= (o[p].Mx - mn) * o[p].cmx;
        if (o[p].mn == o[p].Mx) o[p].mn = mn;
        if (o[p].Mn == o[p].Mx) o[p].Mn = mn;
        if (o[p].tmx > mn) o[p].tmx = mn;
        o[p].Mx = o[p].tmn = mn;
    }
    inline void mark_mx(int p, const int &mx) {
        if (mx <= o[p].Mn) return;
        o[p].s += (mx - o[p].Mn) * o[p].cmn;
        if (o[p].mx == o[p].Mn) o[p].mx = mx;
        if (o[p].Mx == o[p].Mn) o[p].Mx = mx;
        if (o[p].tmn < mx) o[p].tmn = mx;
        o[p].Mn = o[p].tmx = mx;
    }
    inline void down(int p, int l, int r) {
        M; if (o[p].t) mark(goL, o[p].t), mark(goR, o[p].t), o[p].t = 0;
        if (o[p].tmn < INF) mark_mn(ls, o[p].tmn), mark_mn(rs, o[p].tmn), o[p].tmn = INF;
        if (o[p].tmx > -INF) mark_mx(ls, o[p].tmx), mark_mx(rs, o[p].tmx), o[p].tmx = -INF;
    }
    inline void build(int p, int l, int r) {
        if (l == r) {
            o[p].s = o[p].Mn = o[p].Mx = a[l];
            o[p].cmn = o[p].cmx = 1;
            o[p].mn = INF; o[p].mx = -INF;
            return;
        }
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(I, d);
        down(I); M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline void upd_mn(int p, int l, int r, int x, int y, const int &mn) {
        if (l > y || r < x || o[p].Mx <= mn) return;
        if (x <= l && r <= y && o[p].mx < mn) return mark_mn(p, mn);
        down(I); M; upd_mn(goL, x, y, mn); upd_mn(goR, x, y, mn); up(p); 
    }
    inline void upd_mx(int p, int l, int r, int x, int y, const int &mx) {
        if (l > y || r < x || o[p].Mn >= mx) return;
        if (x <= l && r <= y && o[p].mn > mx) return mark_mx(p, mx);
        down(I); M; upd_mx(goL, x, y, mx); upd_mx(goR, x, y, mx); up(p); 
    }
    inline ll query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p].s;
        down(I); M; return query(goL, x, y) + query(goR, x, y);
    }
    inline ll query_mn(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return INF;
        if (x <= l && r <= y) return o[p].Mn;
        down(I); M; return min(query_mn(goL, x, y), query_mn(goR, x, y));
    }
    inline ll query_mx(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return -INF;
        if (x <= l && r <= y) return o[p].Mx;
        down(I); M; return max(query_mx(goL, x, y), query_mx(goR, x, y));
    }
}
using namespace Seg;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    build(1, 1, n);
    io >> m;
    while (m--) {
        int op, l, r, x;
        io >> op >> l >> r;
        if (op == 1) io >> x, upd(1, 1, n, l, r, x);
        else if (op == 2) io >> x, upd_mx(1, 1, n, l, r, x);
        else if (op == 3) io >> x, upd_mn(1, 1, n, l, r, x);
        else if (op == 4) printf("%lld\n", query(1, 1, n, l, r));
        else if (op == 5) printf("%lld\n", query_mx(1, 1, n, l, r));
        else if (op == 6) printf("%lld\n", query_mn(1, 1, n, l, r));
    }

    return 0;
}
