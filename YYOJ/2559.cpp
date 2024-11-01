#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int n, m, C[N << 1][N], ans, a[N][N], b[N][N], s[N][N];

inline void init() {
    For (i, 0, (N << 1) - 1) C[i][0] = 1;
    For (i, 1, (N << 1) - 1) For (j, 1, N - 1) C[i][j] = mo(C[i - 1][j - 1] + C[i - 1][j]);
}

int main() {
    init();
    io >> n >> m;
    For (i, 2, n) For (j, 1, m - 1) a[i][j] = ml(C[i + j - 2][j - 1], C[n - i + j][j]);
    For (i, 1, n - 1) For (j, 2, m) b[i][j] = ml(C[m - j + n - i][m - j], C[m - j + i][i - 1]), s[i][j] = mo(s[i - 1][j] + b[i][j]), add(ans, ml(s[i - 1][j], a[i + 1][j - 1]));
    swap(n, m);
    For (i, 2, n) For (j, 1, m - 1) a[i][j] = ml(C[i + j - 2][j - 1], C[n - i + j][j]);
    For (i, 1, n - 1) For (j, 2, m) b[i][j] = ml(C[m - j + n - i][m - j], C[m - j + i][i - 1]), s[i][j] = mo(s[i - 1][j] + b[i][j]), add(ans, ml(s[i - 1][j], a[i + 1][j - 1]));
    For (i, 2, n) For (j, 1, m - 1) add(ans, ml(a[i][j], b[i - 1][j + 1]));
    mul(ans, 2);
    printf("%d", ans);

    return 0;
}
