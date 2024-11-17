#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: 0; }
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

int T, n, a[30], s[N], f[30][30][2][2], g[30][2], _2[60];

int main() {
    _2[0] = 1; For (i, 1, 59) _2[i] = mo(_2[i - 1] << 1);
    io >> T;
    while (T--) {
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        io >> n;
        int x;
        For (i, 1, n) io >> x, s[i] = s[i - 1] ^ x;
        For (i, 0, 29) g[i][0] = 1;
        For (i, 0, 28) For (j, i + 1, 29) f[i][j][0][0] = 1;
        For (i, 1, n) {
            x = 0;
            For (j, 0, 29) a[j] = s[i] >> j & 1;
            For (j, 0, 29) add(x, ml(g[j][!a[j]], _2[j << 1]));
            For (j, 0, 28) For (k, j + 1, 29) add(x, ml(f[j][k][!a[j]][!a[k]], _2[j + k + 1]));
            For (j, 0, 29) add(g[j][a[j]], x);
            For (j, 0, 28) For (k, j + 1, 29) add(f[j][k][a[j]][a[k]], x);
        }
        printf("%d\n", x);
    }

    return 0;
}
