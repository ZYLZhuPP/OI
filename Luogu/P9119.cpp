#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long double Lf;
const int N = 1e3 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, k, p[N], g[N][N][2];
Lf f[N][N][2], x[N], y[N];

inline Lf dis(int i, int j) {
    i = p[i]; j = p[j];
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

inline void out(int l, int r, int k) {
    if (l < 0 || r > n) return;
    out(l - !k, r + k, g[l][r][k]);
    printf("%d ", p[k? r: l]);
}

int main() {
    io >> n;
    y[0] = -1e8;
    For (i, 1, n) {
        scanf("%Lf%Lf", &x[i], &y[i]);
        if (y[i] > y[k]) k = i;
    }
    For (i, k, n) p[i - k] = i;
    For (i, 1, k) p[n - k + i] = i;
    For (i, 0, n) For (j, 0, n) For (k, 0, 1) f[i][j][k] = 1e18;
    f[0][n][0] = f[0][n][1] = 0;
    For (l, 0, n) rFor (r, n, l + 2) {
        f[l + 1][r][0] = f[l][r][0] + dis(l, l + 1);
        if (cmin(f[l + 1][r][0], f[l][r][1] + dis(l + 1, r))) g[l + 1][r][0] = 1;
        f[l][r - 1][1] = f[l][r][0] + dis(l, r - 1);
        if (cmin(f[l][r - 1][1], f[l][r][1] + dis(r - 1, r))) g[l][r - 1][1] = 1;
    }
    int pos = 0, k = 0;
    For (i, 0, n - 1) For (j, 0, 1) if (cmin(f[0][0][0], f[i][i + 1][j])) pos = i, k = j;
    out(pos, pos + 1, k);

    return 0;
}
