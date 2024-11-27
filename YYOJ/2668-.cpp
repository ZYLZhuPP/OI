#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105, Mo = 998244353;
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

int n, m, a[N], f[N][N][N];

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    For (i, 1, n + 1) f[0][i][i - 1] = 1;
    For (i, 1, n) {
        f[0][i][i] = 1;
        For (j, i + 1, n) if (a[j] > a[j - 1]) f[0][i][j] = 1; else break;
    }
    For (i, 0, m - 1) {
        For (l, 1, n + 1) For (r, l - 1, n) if (f[i][l][r]) {
            int len = r - l + 1, x = f[i][l][r];
            add(f[i + 1][l][r], ml(n - len, 2 * x));
            if (l > 1) add(f[i + 1][l - 1][r], x);
            if (r < n) add(f[i + 1][l][r + 1], x);
        }
    }
    printf("%d", f[m][1][n]);

    return 0;
}
