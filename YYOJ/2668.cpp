#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 998244353;
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

int n, m, a[N], f[N][N], C[N][N], ans;

int main() {
    io >> n >> m;
    For (i, 0, n) C[i][0] = 1;
    For (i, 1, n) For (j, 1, i) C[i][j] = mo(C[i - 1][j] + C[i - 1][j - 1]);
    For (i, 1, n) io >> a[i];
    f[0][0] = 1;
    For (i, 1, m) For (j, 1, i) f[i][j] = mo(f[i - 1][j - 1] + ml(2 * j, f[i - 1][j]));
    For (i, 1, n) For (j, i, n) {
        add(ans, ml(f[m][n - (j - i + 1)], C[n - (j - i + 1)][i - 1]));
        if (a[j + 1] < a[j]) break;
    }
    For (i, 0, n) add(ans, ml(f[m][n], C[n][i]));
    printf("%d", ans);

    return 0;
}
