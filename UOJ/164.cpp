#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e18;
const int N = 5e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, m, val[N];

namespace Seg {
    ll a[N << 2][2], b[N << 2][2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void mark(int p, ll x, ll y, ll X, ll Y) {
        cmax(a[p][1], a[p][0] + X); cmax(b[p][1], max(b[p][0] + X, Y));
        a[p][0] = max(a[p][0] + x, -INF); b[p][0] = max(b[p][0] + x, y);
    }
    inline void down(int p) { mark(ls, a[p][0], b[p][0], a[p][1], b[p][1]), mark(rs, a[p][0], b[p][0], a[p][1], b[p][1]), a[p][0] = a[p][1] = 0, b[p][0] = b[p][1] = -INF; }
    inline void upd(int p, int l, int r, int x, int y, ll a, ll b) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, a, b ,a, b);
        down(p); M; upd(goL, x, y, a, b); upd(goR, x, y, a, b);
    }
    inline ll query(int p, int l, int r, int x, int op) {
        if (l > x || r < x) return -INF;
        if (l == r) return max(val[x] + a[p][op], b[p][op]);
        down(p); M; return max(query(goL, x, op), query(goR, x, op));
    }
}
using namespace Seg;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> val[i];
    while (m--) {
        int op, l, r; ll x;
        io >> op;
        if (op <= 3) {
            io >> l >> r >> x;
            if (op == 1) upd(1, 1, n, l, r, x, -INF);
            else if (op == 2) upd(1, 1, n, l, r, -x, 0);
            else if (op == 3) upd(1, 1, n, l, r, -INF, x);
        } else io >> x, printf("%lld\n", query(1, 1, n, x, op - 4));
    }

    return 0;
}
