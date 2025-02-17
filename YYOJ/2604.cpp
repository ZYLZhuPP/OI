#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5, Mo = 1e9 + 7;
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

int n, q, a[N], s[N], _s[N], b[N], f[N], g[N];

int main() {
    io >> n >> q;
    For (i, 1, n) io >> a[i], s[i] = s[i - 1] + a[i], _s[i] = qPow(s[i], Mo - 2);
    For (i, 1, n) io >> b[i];
    int x = ml(a[1], b[1]);
    For (i, 2, n) f[i] = mo(ml(x, _s[i - 1]) + b[i]), add(x, ml(a[i], f[i] + b[i]));
    x = 0;
    For (i, 2, n) {
        int y = ml(a[i], _s[i]);
        g[i] = mo(ml(y, f[i]) + ml(mo(1 - y), ml(x, _s[i - 1])));
        add(x, ml(a[i], g[i]));
    }
    int u, v;
    while (q--) {
        io >> u >> v; if (u > v) swap(u, v);
        printf("%d\n", u==v? 0: mo(mo(f[u] + f[v]) - ml(2, g[u])));
    }

    return 0;
}
