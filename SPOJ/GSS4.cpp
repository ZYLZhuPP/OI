#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int T, n, m;
ll a[N];

namespace Seg {
    ll mx[N << 2], mn[N << 2], s[N << 2], t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void up(int p) { mx[p] = max(mx[ls], mx[rs]); mn[p] = min(mn[ls], mn[rs]); s[p] = s[ls] + s[rs]; }
    inline void mark(int p, int l, int r, ll d) { mx[p] += d; mn[p] += d; s[p] += (r - l + 1) * d; t[p] += d; }
    inline void down(int p, int l, int r) { M; if (t[p]) mark(goL, t[p]), mark(goR, t[p]), t[p] = 0; }
    inline void build(int p, int l, int r) {
        t[p] = 0;
        if (l == r) return mx[p] = mn[p] = s[p] = a[l], void();
        M; build(goL); build(goR); up(p);
    }
    inline ll D(ll x) { return (int)sqrt(x) - x; }
    inline void sq(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return;
        if (x <= l && r <= y && D(mx[p]) == D(mn[p])) return mark(I, D(mx[p]));
        down(I); M; sq(goL, x, y); sq(goR, x, y); up(p);
    }
    inline ll query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return s[p];
        down(I); M; return query(goL, x, y) + query(goR, x, y);
    }
}
using namespace Seg;

int main() {
    while (~(io >> n)) {
        printf("Case #%d:\n", ++T);
        For (i, 1, n) io >> a[i];
        build(1, 1, n);
        io >> m;
        while (m--) {
            int op, l, r;
            io >> op >> l >> r; if (l > r) swap(l, r);
            if (op == 0) sq(1, 1, n, l, r);
            else printf("%lld\n", query(1, 1, n, l, r));
        }
        puts("");
    }

    return 0;
}