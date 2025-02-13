#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

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

int n, q, a[N];

namespace Seg {
    bool o[N << 2]; int to[N << 2][50]; ll t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void init(int p) { For (i, 0, 49) to[p][i] = i; o[p] = 0; }
    inline void pop(int p) { For (i, 0, 49) to[p][i] = __builtin_popcountll(to[p][i] + t[p]); t[p] = 0; }
    inline void merge(int q, int p) { For (i, 0, 49) to[q][i] = to[p][to[q][i]]; o[q] = 1; }
    inline void mark(int p, const ll &d) { t[p] += d; }
    inline void down(int p) { if (o[p]) merge(ls, p), merge(rs, p), init(p); if (t[p]) mark(ls, t[p]), mark(rs, t[p]), t[p] = 0; }
    inline void build(int p, int l, int r) {
        init(p);
        if (l == r) return o[p] = 1, t[p] = a[l], void();
        M; build(goL); build(goR);
    }
    inline void pop(int p, int l, int r) {
        if (o[p]) return pop(p);
        down(p); M; pop(goL); pop(goR); o[p] = 1;
    }
    inline void pop(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return pop(I);
        down(p); M; pop(goL, x, y); pop(goR, x, y);
    }
    inline void upd(int p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, d);
        down(p); M; upd(goL, x, y, d); upd(goR, x, y, d);
    }
    inline ll query(int p, int l, int r, int x) {
        if (l == r) return to[p][0] + t[p];
        M; return (x<=m? (o[p]? to[p][query(goL, x)]: query(goL, x)): (o[p]? to[p][query(goR, x)]: query(goR, x))) + t[p];
    }
}
using namespace Seg;

int main() {
    io >> n >> q;
    For (i, 1, n) io >> a[i];
    build(1, 1, n);
    while (q--) {
        char op[2]; int l, r, x;
        scanf("%s", op);
        if (op[0] == 'A') io >> l >> r >> x, upd(1, 1, n, l, r, x);
        else if (op[0] == 'P') io >> l >> r, pop(1, 1, n, l, r);
        else io >> x, printf("%lld\n", query(1, 1, n, x));
    }

    return 0;
}
