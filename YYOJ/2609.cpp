#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5, Mo = 1e9 + 7;
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

int n, m, C[N][N], f[N][N], vis[N][N], ans;

inline void init() {
    For (i, 0, N - 1) C[i][0] = 1;
    For (i, 1, N - 1) For (j, 1, i) C[i][j] = mo(C[i - 1][j] + C[i - 1][j - 1]);
}

inline int dp(int i, int j, int k) {
    if (i < 0) return 0;
    if (j == 1) return i <= k;
    if (!i) return 1;
    if (vis[i][m - j] == k) return f[i][m - j];
    vis[i][m - j] = k;
    return f[i][m - j] = ml(j, mo(dp(i - 1, j, k) - ml(dp(i - k - 1, j - 1, k), C[i - 1][k])));
}

int main() {
    init();
    io >> n >> m;
    memset(vis, -1, sizeof vis);
    int x = qPow(qPow(m, n), Mo - 2);
    For (i, 0, n) add(ans, 1 - ml(dp(n, m, i), x));
    printf("%d", ans);

    return 0;
}
