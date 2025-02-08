#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int Mo = 1e9 + 9;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

namespace Cat {
    int o[21][1 << 20];
#define lg(x) (32 - __builtin_clz(x))
    inline void build(int l, int r, int k) {
        if (l == r) return void(o[k][l] = l);
        int m = (l + r) >> 1;
        o[k][m] = m; rFor (i, m - 1, l) o[k][i] = ml(o[k][i + 1], i);
        o[k][m + 1] = m + 1; For (i, m + 2, r) o[k][i] = ml(o[k][i - 1], i);
        build(l, m, k - 1); build(m + 1, r, k - 1);
    }
    inline int query(int l, int r) {
        if (l > r) return 1;
        if (l == r) return o[0][l];
        int k = lg(l ^ r);
        return ml(o[k][l], o[k][r]);
    }
}
using namespace Cat;

int n, m;

int main() {
    io >> n >> m;
    build(0, (1 << lg(n)) - 1, lg(n));
    while (m--) {
        int l, r;
        io >> l >> r;
        printf("%d\n", query(l, r));
    }

    return 0;
}
