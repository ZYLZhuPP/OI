#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 35, M = 905, Mo = 998244353;
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

int n, m, f[N][N][M], C[M][M], ans;

inline void init() {
    For (i, 0, M - 1) C[i][0] = 1;
    For (i, 1, M - 1) For (j, 1, i) C[i][j] = mo(C[i - 1][j] + C[i - 1][j - 1]);
}

int main() {
    init();
    io >> n >> m;
    f[0][0][0] = 1;
    For (i, 0, n) For (j, 0, n - i) For (k, 0, m) if (f[i][j][k]) {
        int v = f[i][j][k];
        For (x, 0, i) add(f[i + 1][j][k + x], ml(C[i][x], v));
        For (x, 0, j) add(f[i][j + 1][k + i + x], ml(C[j][x], v));
    }
    For (i, 0, n) add(ans, f[i][n - i][m]);
    add(ans, -C[n * (n - 1) / 2][m]);
    printf("%d", ans);

    return 0;
}
