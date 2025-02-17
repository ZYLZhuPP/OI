#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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

int n, q, t[N];
vector<array<int, 2 > > es;

namespace Seg {
    struct Node { int mn, c, d, ad; ll s; } o[N << 2];
#define ls p << 1 
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) {
        int l = o[ls].mn <= o[rs].mn, r = o[rs].mn <= o[ls].mn;
        o[p].mn = o[ls | r].mn + o[p].d;
        o[p].c = (l? o[ls].c: 0) + (r? o[rs].c: 0);
        o[p].s = (l? o[ls].s: 0) + (r? o[rs].s: 0) + 1ll * o[p].c * o[p].ad;
    }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p].mn = 1 - l, o[p].c = 1, void();
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return o[p].ad += d, o[p].s += 1ll * o[p].c * d, void();
        M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline void Upd(int p, int l, int r, int x, int y, const int &d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return o[p].d += d, o[p].mn += d, void();
        M; Upd(goL, x, y, d); Upd(goR, x, y, d); up(p);
    }
}
using namespace Seg;

inline void add(int u, int v, int d) {
    if (t[u] > t[v]) swap(u, v);
    Upd(1, 1, n - 1, t[u], n - 1, d);
    upd(1, 1, n - 1, t[u], t[v] - 1, d);
}

int main() {
    io >> n >> q;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es.pb({u, v});
    t[1] = n;
    For (i, 1, n - 1) io >> u, t[u] = i;
    build(1, 1, n - 1);
    for (auto &[u, v] : es) add(u, v, 1);
    printf("%lld\n", o[1].s);
    int x, y;
    while (q--) io >> x >> y >> u >> v, add(x, y, -1), add(u, v, 1), printf("%lld\n", o[1].s);

    return 0;
}
