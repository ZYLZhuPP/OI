#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e4 + 5;

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
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, op[N], l[N], r[N], B;
ll x[N], b[N];

namespace Seg {
    struct Node { int l, r, t; ll sz; } o[N * 300];
    int tot;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void up(int p) { o[p].sz = o[ls].sz + o[rs].sz; }
    inline void mark(int &p, int l, int r, const int &d) { if (!p) p = ++tot; o[p].sz += 1ll * (r - l + 1) * d; o[p].t += d; }
    inline void down(int p, int l, int r) { M; if (o[p].t) mark(goL, o[p].t), mark(goR, o[p].t), o[p].t = 0; }
    inline void upd(int &p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (!p) p = ++tot;
        if (x <= l && r <= y) return mark(I, d);
        down(I); M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline ll query(int p, int l, int r, int x, int y) {
        if (!p || l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p].sz;
        down(I); M; return query(goL, x, y) + query(goR, x, y);
    }
#undef ls
#undef rs
    int rt[N << 2];
#define ls p << 1 
#define rs p << 1 | 1
    inline void Upd(int p, int l, int r, int x, int a, int b) {
        if (l > x || r < x) return;
        upd(rt[p], 1, n, a, b, 1);
        if (l == r) return;
        M; Upd(goL, x, a, b); Upd(goR, x, a, b);
    }
    inline int Query(int p, int l, int r, int x, int y, ll k) {
        if (l == r) return l;
        ll d = query(rt[rs], 1, n, x, y);
        M; return k<=d? Query(goR, x, y, k): Query(goL, x, y, k - d);
    }
}
using namespace Seg;

int main() {
    io >> n >> m;
    For (i, 1, m) {
        io >> op[i] >> l[i] >> r[i] >> x[i];
        if (op[i] == 1) b[++B] = x[i];
    }
    sort(b + 1, b + B + 1); B = unique(b + 1, b + B + 1) - b - 1;
    For (i, 1, m) {
        if (op[i] == 1) {
            x[i] = lower_bound(b + 1, b + B + 1, x[i]) - b;
            Upd(1, 1, B, x[i], l[i], r[i]);
        } else if (op[i] == 2) printf("%lld\n", b[Query(1, 1, B, l[i], r[i], x[i])]);
    }

    return 0;
}
