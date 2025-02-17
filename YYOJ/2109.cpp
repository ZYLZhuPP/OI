#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2005, M = 6005, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline IO& operator >> (char &x) {
        while ((c = gc()) < 33 && ~c);
        x = c; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, g[3][N], f[N][M][2], ans, c[N];
int inv[M], fac[M], invfac[M];
char ch;

void check() {
    bool ok = 1;
    if (!g[0][1] || !g[0][n] || !g[2][1] || !g[0][n]) ok = 0;
    For (i, 3, n - 1) ok &= (g[0][i] || g[0][i - 1]) && (g[2][i] || g[2][i - 1]);
    if (!ok) { puts("0"); exit(0); }
}

void init() {
    inv[0] = inv[1] = 1;
    For (i, 2, M - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = invfac[0] = 1;
    For (i, 1, M - 1) fac[i] = ml(fac[i - 1], i), invfac[i] = ml(invfac[i - 1], inv[i]);
    //For (i, 1, 5) cout << ml(fac[i], invfac[i]) << endl;
}
int A(int n, int m) { return ml(fac[n], invfac[n - m]); }

int main() {
    init();
    io >> n;
    For (i, 0, 2) For (j, 1, n) io >> ch, g[i][j] = ch == 'o';
    check();
    For (i, 1, n) c[i] = !g[0][i] + !g[2][i];

    int s = !g[1][1]; //cout << s << endl;
    f[1][s][0] = 1;
    For (i, 2, n) {
        For (j, 1, s) add(f[i - 1][j][0], f[i - 1][j - 1][0]), add(f[i - 1][j][1], f[i - 1][j - 1][1]);
        int k = c[i];
        s += k + !g[1][i]; //cout << s << endl;
        if (g[1][i]) add(f[i][0][0], ml(mo(f[i - 1][s - k][0] + f[i - 1][s - k][1]), A(s, k)));
        else For (j, 1, s) {
            if (j >= k + 1) add(f[i][j][0], ml(mo(f[i - 1][s - k - 1][1] - f[i - 1][j - k - 1][1] + f[i - 1][s - k - 1][0]), A(j - 1, k)));
            //cout << f[i][j][0] << endl;
            if (k) {
                add(f[i][j][1], ml(f[i - 1][j - 1][0], A(s - j, k)));
                if (k == 2 && j >= 2) add(f[i][j][1], ml(f[i - 1][j - 2][0], 2 * (s - j) * (j - 1)));
            }
        }
    }

    For (i, 0, s) add(ans, f[n][i][0]);

    printf("%d", ans);

    return 0;
}
