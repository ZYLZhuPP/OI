#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5, inf = 1e5;
const ll Mo = 1e17 + 1921;
inline ll mo(ll x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(ll &x, const ll &y) { x = mo(x + y); }

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

int n, q, rt[N];
ll w[N];
mt19937_64 rnd(Mo);

namespace Seg {
    struct Node {
        int l, r; ll v;
        Node() { l = r = v = 0; }
    } o[N << 5];
    int tot;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define LL o[q].l, o[P].l, o[Q].l
#define RR o[q].r, o[P].r, o[Q].r
    inline void copy(int &p) { o[++tot] = o[p]; p = tot; }
    inline void up(int p) { o[p].v = mo(o[ls].v + o[rs].v); }
    inline void upd(int &p, int l, int r, int x) {
        copy(p);
        if (l == r) return add(o[p].v, w[x]);
        M; x<=m? upd(goL, x): upd(goR, x); up(p);
    }
    inline ll val(int p, int q) { return mo(o[p].v - o[q].v); }
    inline bool check(int p, int q, int P, int Q) { return val(p, q) == val(P, Q); }
    inline int query(int p, int l, int r, int q, int P, int Q, int k) {
        if (l == r) {
            ll x = mo(val(p, q) - val(P, Q));
            return !x? 0: x==w[l]? 1: -1;
        }
        bool L = check(ls, LL), R = check(rs, RR); M;
        if (!L && !R) return 0;
        if (k && !L && val(rs, o[q].r)) return 0;
        if (!k && !R && val(ls, o[q].l)) return 0;
        return !L? query(goL, LL, k): query(goR, RR, k);
    }
    inline bool ok(int p, int l, int r, int q, int P, int Q) {
        bool L = check(ls, LL), R = check(rs, RR); M;
        if (!L && !R) {
            int a = query(goL, LL, 1), b = query(goR, RR, 0);
            return abs(a) == 1 && !(a + b);
        }
        return !L? ok(goL, LL): !R? ok(goR, RR): 1;
    }
}
using namespace Seg;

int main() {
    io >> n >> q;
    For (i, 1, inf) w[i] = rnd() % Mo;
    int x;
    For (i, 1, n) io >> x, upd(rt[i] = rt[i - 1], 1, inf, x);
    int a, b, c, d;
    while (q--) {
        io >> a >> b >> c >> d;
        puts(ok(rt[b], 1, inf, rt[a - 1], rt[d], rt[c - 1])? "YES": "NO");
    }

    return 0;
}
