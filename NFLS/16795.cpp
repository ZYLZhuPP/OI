#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 35;

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

int n, m;
ll len[N][N], p;
bool f[N * 2][N][N];
char a[N], b[N], c[N][N];

inline void out(int x, int y, ll l, ll r) {
    if (!x || !y) putchar(c[x][y]);
    else if (f[x + y - 1][y - 1][y]) {
        ll z = len[x][y - 1];
        if (l <= z) out(x, y - 1, l, min(r, z));
        if (r > z) out(x - 1, y, max(1ll, l - z), r - z);
    } else {
        ll z = len[x - 1][y];
        if (l <= z) out(x - 1, y, l, min(r, z));
        if (r > z) out(x, y - 1, max(1ll, l - z), r - z);
    }
}

int main() {
    scanf("%s", a + 1); n = strlen(a + 1);
    scanf("%s", b + 1); m = strlen(b + 1);
    For (i, 1, n) c[i][0] = a[i], len[i][0] = 1;
    For (i, 1, m) c[0][i] = b[i], len[0][i] = 1;
    For (i, 1, n) For (j, 1, m) c[i][j] = min(c[i - 1][j], c[i][j - 1]), len[i][j] = len[i - 1][j] + len[i][j - 1];
    For (i, 1, n + m - 1) {
        int l = max(0, i - n), r = min(i, m);
        For (j, l, r - 1) For (k, j + 1, r) {
            if (!j || k == i) { f[i][j][k] = c[i - j][j] < c[i - k][k]; continue; }
            int x = j - f[i - 1][j - 1][j], y = k - f[i - 1][k - 1][k];
            f[i][j][k] = x^y? f[i - 1][x][y]: f[i - 1][j - 1][k];
        }
    }
    io >> p;
    out(n, m, p + 1, min(len[n][m], p + 50));

    return 0;
}
