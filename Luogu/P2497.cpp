#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
const int N = 5e5 + 5;
const lf inf = 1e20;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, r[N], v[N];
ll m, x[N];
lf y[N], f[N], ans = inf;

namespace Seg {
    struct Line {
        lf k, b;
        Line(lf k = inf, lf b = inf): k(k), b(b) { }
    } o[N << 2];
    inline lf F(const Line &v, const int &i) { return v.k * x[i] + v.b; }
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void upd(int p, int l, int r, Line v) {
        M; if (F(v, m) < F(o[p], m)) swap(o[p], v);
        if (F(v, l) < F(o[p], l)) upd(goL, v);
        if (F(v, r) < F(o[p], r)) upd(goR, v);
    }
    inline lf query(int p, int l, int r, int x) {
        if (l > x || r < x) return inf;
        if (l == r) return F(o[p], x);
        M; return min(F(o[p], x), min(query(goL, x), query(goR, x)));
    }
}
using namespace Seg;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> x[i] >> r[i] >> v[i], y[i] = 0.5 / sqrt(r[i]);
    For (i, 1, n) {
        f[i] = (i>1? query(1, 1, n, i): 0) + v[i];
        upd(1, 1, n, {y[i], f[i] - x[i] * y[i]});
        if (x[i] + r[i] >= m) cmin(ans, f[i]);
    }
    printf("%.3lf", ans);

    return 0;
}
