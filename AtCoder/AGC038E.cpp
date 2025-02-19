#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 405, Mo = 998244353;
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

int n, a[N], b[N], A, B, inv[N], fac[N], ivf[N], f[N][N][N], g[N][N], ans;

inline void init() {
    inv[1] = 1; For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1; For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
}

int main() {
    init();
    io >> n;
    For (i, 1, n) {
        io >> a[i] >> b[i], A += a[i], B += b[i] - 1;
        g[i][0] = 1; For (j, 1, b[i] - 1) g[i][j] = ml(g[i][j - 1], a[i]);
    }
    f[0][0][0] = -1;
    For (i, 1, n) For (j, 0, A) For (k, 0, B) {
        f[i][j][k] = f[i - 1][j][k];
        if (a[i] <= j) For (l, 0, b[i] - 1) if (l <= k) add(f[i][j][k], -ml(f[i - 1][j - a[i]][k - l], ml(g[i][l], ivf[l])));
    }
    For (j, 1, A) For (k, 0, B) add(ans, ml(ml(A, qPow(inv[j], k + 1)), ml(f[n][j][k], fac[k])));
    printf("%d", ans);

    return 0;
}
