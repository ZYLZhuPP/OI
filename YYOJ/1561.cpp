#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105, Mo = 1e9 + 7;
inline int mo(int &x) {return x -= x >= Mo? Mo: 0;}
inline int gmo(int x) {return mo(x);}

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

int T, n, m, _2[N * N], inv[N], fac[N], invfac[N], C[N][N], g[N], h[N][N], f[N][N];

int qPow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % Mo;
        a = 1ll * a * a % Mo;
        b >>= 1;
    }
    return res;
}

void init() {
    _2[0] = 1;
    For (i, 1, 10000) _2[i] = gmo(_2[i - 1] << 1);
    inv[0] = inv[1] = 1;
    For (i, 2, 100) inv[i] = 1ll * (Mo - Mo / i) * inv[Mo % i] % Mo;
    fac[0] = invfac[0] = 1;
    For (i, 1, 100) fac[i] = 1ll * fac[i - 1] * i % Mo, invfac[i] = 1ll * invfac[i - 1] * inv[i] % Mo;
    For (i, 0, 100) For (j, 0, i) C[i][j] = 1ll * fac[i] * invfac[i - j] % Mo * invfac[j] % Mo;
    g[1] = 1;
    For (i, 2, 100) {
        For (j, 1, i - 1) g[i] = gmo(g[i] + 1ll * g[j] * _2[C[i - j][2]] % Mo * C[i - 1][j - 1] % Mo);
        g[i] = gmo(_2[C[i][2]] - g[i] + Mo);
    }
    For (i, 1, 100) For (j, 1, 100) h[i][j] = 1ll * g[j] * qPow(_2[j] - 1, i) % Mo * _2[C[i][2]] % Mo;
    For (i, 0, 100) f[i][0] = _2[C[i][2]];
    For (i, 1, 100) {
        For (j, 1, i) {
            For (k, 1, j) f[i][j] = gmo(f[i][j] + 1ll * C[j - 1][k - 1] * f[i - k][j - k] % Mo);
            For (k, 1, j)
                For (l, 1, i - j) f[i][j] = gmo(f[i][j] + 1ll * f[i - k - l][j - k] * C[j - 1][k - 1] % Mo * C[i - j][l] % Mo * h[k][l] % Mo);
        }
    }
}

int main() {
    init();
    io >> T;
    while (T--) {
        io >> n >> m;
        printf("%d\n", f[n][m]);
    }

    return 0;
}
