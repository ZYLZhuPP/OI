#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105;
int Mo;
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

int n, ans, C[N][N], g[N][N * N];

inline void init() {
    For (i, 0, n) C[i][0] = 1;
    For (i, 1, n) For (j, 1, i) C[i][j] = mo(C[i - 1][j - 1] + C[i - 1][j]);
}

int main() {
    io >> n >> Mo;
    init();
    For (i, 1, n) {
        For (j, 1, i - 1) add(g[i][j * j + (i - j) * (i - j)], C[i - 1][j - 1]);
        For (j, 1, i - 1) For (k, 0, j * j - 1) add(g[i][k + (i - j) * (i - j)], -ml(g[j][k], C[i - 1][j - 1]));
    }
    For (i, 0, n * n - 1) add(ans, ml(g[n][i], qPow(n * n - i, Mo - 2)));
    mul(ans, n * n);
    printf("%d", ans);

    return 0;
}
