#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5, Mo = 1e9 + 7;
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

int _2[N], inv[N], fac[N], ivf[N], s[N][N], n, q;

inline int C(int n, int m) { return ml(fac[n], ml(ivf[n - m], ivf[m])); }

inline void init() {
    _2[0] = 1;
    For (i, 1, N - 1) _2[i] = mo(_2[i - 1] << 1);
    inv[1] = 1;
    For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1;
    For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
    For (i, 1, N - 1) For (j, 1, i) s[i][j] = mo(s[i][j - 1] + ml(ml(_2[i - j], ml(j, j)), ml(i - j, C(i, j))));
}

int main() {
    init();
    io >> n >> q;
    int a, b, c;
    while (q--) io >> a >> b >> c, printf("%d\n", mo(s[c][b] - s[c][a - 1]));

    return 0;
}
