#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, m, a[N], cnt[N];
set<int > se;
vector<int > del;

namespace Seg {
    int b[N << 2], o[N << 2][24], s[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { s[p] = mo(s[ls] + s[rs]); }
    inline void Up(int p) { For (i, 0, 23) o[p][i] = mo(o[ls][(b[ls] + i) % 24] + o[rs][(b[rs] + i) % 24]); }
    inline void build(int p, int l, int r) {
        if (l == r) return s[p] = a[l], void();
        M; build(goL); build(goR); up(p);
    }
    inline void init(int p, int l, int r, int x, int v) {
        if (l > x || r < x) return;
        if (l == r) {
            add(s[p], -a[l]);
            For (i, 0, 23) o[p][i] = v, mul(v, v);
            assert(o[p][0] == v);
            return;
        }
        M; init(goL, x, v); init(goR, x, v); up(p); Up(p);
    }
    inline void upd(int p, int l, int r, int x, int v) {
        if (l > x || r < x) return;
        if (l == r) return add(s[p], v - a[l]), a[l] = v, void();
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline void Upd(int p, int l, int r, int x, int y, int d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return (b[p] += d) %= 24, void();
        M; Upd(goL, x, y, d); Upd(goR, x, y, d); Up(p);
    }
    inline int query(int p, int l, int r, int x, int y, int d) {
        if (l > y || r < x) return 0;
        (d += b[p]) %= 24;
        if (x <= l && r <= y) return mo(s[p] + o[p][d]);
        M; return mo(query(goL, x, y, d) + query(goR, x, y, d));
    }
}
using namespace Seg;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], a[i] = qPow(a[i], Mo - 2), se.insert(i);
    build(1, 1, n);
    while (m--) {
        int op, l, r;
        io >> op >> l >> r;
        if (op == 0) {
            for (auto it = se.lower_bound(l); it != se.end() && *it <= r; it++) {
                int x = *it;
                if (++cnt[x] < 24) upd(1, 1, n, x, ml(a[x], a[x]));
                else del.pb(x);
            }
            Upd(1, 1, n, l, r, 1);
            for (auto &x : del) {
                init(1, 1, n, x, ml(a[x], a[x]));
                se.erase(x);
            }
            del.resize(0);
        } else printf("%d\n", query(1, 1, n, l, r, 0));
    }

    return 0;
}
