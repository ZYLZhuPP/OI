#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e6 + 5, Mo = 998244353;
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

int n, T, k, _2[N], inv[N], fac[N], ivf[N], f[N];

inline int C(int n, int m) { return ml(fac[n], ml(ivf[m], ivf[n - m])); }

void init() {
    _2[0] = 1;
    For (i, 1, N - 1) _2[i] = mo(_2[i - 1] << 1);
    inv[1] = 1;
    For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1;
    For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
    f[0] = 1;
    For (i, 2, N - 1) f[i] = mo(ml(ml(4 * i, i - 1), f[i - 1]) + ml(ml(i - 1, i - 1), ml(8 * i, f[i - 2])));
}

int main() {
    init();
    io >> T;
    while (T--) io >> n >> k, printf("%d\n", ml(ml(C(n, k), C(n, k)), ml(ml(fac[k], _2[k]), f[n - k])));
    
    return 0;
}
