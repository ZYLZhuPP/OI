#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 305, M = N * N;
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

int n, K, K0, K1, x[M], y[M], w[N][N], d[2][5][N][N], ans[M];

inline void upd(int o, int k, int u, int v, int w) {
    d[o][1][u][v] = w;
    if (k == 1) return;
    For (i, 1, n) cmin(d[o][2][u][i], w + d[o][1][v][i]), cmin(d[o][2][i][v], w + d[o][1][i][u]);
    int rt = o? n: 1, k0 = k / 2, k1 = k - k0;
    if (rt == u) For (i, 1, n) For (j, 1, n) cmin(d[o][k][rt][j], d[o][k0][rt][i] + d[o][k1][i][j]);
    For (i, 1, n) cmin(d[o][k][rt][i], d[o][k0][rt][u] + d[o][k1][u][i]), cmin(d[o][k][rt][i], d[o][k0][rt][v] + d[o][k1][v][i]), cmin(d[o][k][rt][v], d[o][k0][rt][i] + d[o][k1][i][v]);
}

inline int get() {
    int res = 1e9;
    For (i, 1, n) cmin(res, d[0][K0][1][i] + d[1][K1][n][i]);
    return res<1e9? res: -1;
}

int main() {
    memset(d, 63, sizeof d);
    io >> n >> K; K0 = K / 2, K1 = K - K0;
    For (i, 1, n) For (j, 1, n) io >> w[i][j];
    For (i, 1, n * n) io >> x[i] >> y[i];
    rFor (i, n * n, 1) {
        ans[i] = get();
        upd(0, K0, x[i], y[i], w[x[i]][y[i]]);
        upd(1, K1, y[i], x[i], w[x[i]][y[i]]);
    }
    For (i, 1, n * n) printf("%d\n", ans[i]);

    return 0;
}
