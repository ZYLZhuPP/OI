#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 205;

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

int n, L, K, x, a[N];
long double p[N], f[N][N][N << 1], ans;

int main() {
    io >> n >> L >> K; K = min(K, n) + n;
    For (i, 1, n) io >> x, p[i] = 0.01L * x;
    For (i, 1, n) io >> a[i];

    f[0][0][K] = 1;
    For (i, 0, n - 1) For (j, 0, i) For (k, 0, 2 * n) if (f[i][j][k]) {
        f[i + 1][j][k] += (1 - p[i + 1]) * f[i][j][k];
        if (k + a[i + 1] >= 0) f[i + 1][j + 1][min(2 * n, k + a[i + 1])] += p[i + 1] * f[i][j][k];
    }

    For (j, L, n) For (k, n, 2 * n) ans += f[n][j][k];
    printf("%.6Lf", ans);

    return 0;
}