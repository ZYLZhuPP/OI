#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int T, n, K, a[2][N], b[2][N], m[2], g[N][N], h[2][N], f[2][N][N];

int main() {
    io >> T >> n >> K;
    char op[4]; int x, y;
    For (i, 1, n) {
        scanf("%s", op); bool c = op[0] == 'G';
        io >> x >> y;
        a[c][++m[c]] = x; b[c][m[c]] = (T&1? -1: 1) * y;
    }
    rFor (i, m[0], 1) rFor (j, m[1], 1) if (abs(a[0][i] - a[1][j]) <= K) g[i][j] = g[i + 1][j + 1] + 1;
    For (k, 0, 1) For (i, 1, m[k]) rFor (j, m[!k], 1) if (a[!k][j] - a[k][i] > K) h[k][i] = j;
    memset(f, -63, sizeof f);
    f[0][0][0] = f[1][0][0] = 0;
    For (i, 0, m[0]) For (j, 0, m[1]) {
        int k = max(h[0][i] - j - 1, 0);
        if (i && h[0][i] && k <= g[i + 1][j + 1]) cmax(f[1][i + k][j + k], f[0][i][j]);
        k = max(h[1][j] - i - 1, 0);
        if (j && h[1][j] && k <= g[i + 1][j + 1]) cmax(f[0][i + k][j + k], f[1][i][j]);
        cmax(f[0][i + 1][j], f[0][i][j] + b[0][i + 1]);
        cmax(f[1][i][j + 1], f[1][i][j] + b[1][j + 1]);
        if (g[i + 1][j + 1]) For (k, 0, 1) cmax(f[k][i + 1][j + 1], f[k][i][j]);
    }
    printf("%d", (T&1? -1: 1) * max(f[0][m[0]][m[1]], f[1][m[0]][m[1]]));

    return 0;
}
