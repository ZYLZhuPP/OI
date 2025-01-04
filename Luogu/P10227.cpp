#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 1e9 + 7, inv2 = 5e8 + 4;
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

int n, fa[N], d[N], a[N], inv[N] = {1, 1}, _[N] = {1, inv2}, f[N], g[N], h[N];

int main() {
	io >> n;
    For (i, 2, n) _[i] = ml(_[i - 1], inv2), inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
	For (i, 2, n) io >> fa[i], ++d[fa[i]];
	For (i, 1, n) io >> a[i], h[i] = ml(inv[i], Mo + 1 - _[i]);
	rFor (i, n, 1) f[i] = mo(a[i] + ml(g[i], h[d[i]])), add(g[fa[i]], f[i]);
	For (i, 2, n) add(g[i], mo(a[fa[i]] + ml(g[fa[i]] - f[i], h[d[fa[i]] - 1]))), f[i] = mo(a[i] + ml(g[i], h[++d[i]]));
	For (i, 1, n) printf("%d\n", f[i]);

	return 0;
}