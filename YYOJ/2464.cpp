#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e3 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

const int dx[6] = {0, -1, -1, 0, 1, 1}, dy[6] = {-2, -1, 1, 2, 1, -1};
int n, a[N][N], bl[N], br[N], f[N][N][6], g[N][N][6];

int main() {
    io >> n;
    For (i, 1, 2 * n - 1) {
        bl[i] = abs(i - n) + 1; br[i] = 4 * n - 3 - abs(i - n);
        for (int j = bl[i]; j <= br[i]; j += 2) {
            io >> a[i][j];
            For (k, 0, 5) g[i][j][k] = f[i][j][k] = 1;
        }
    }
    For (i, 1, 2 * n - 1) for (int j = bl[i]; j <= br[i]; j += 2) {
        For (k, 0, 2) {
            int x = i + dx[k], y = j + dy[k];
            if (a[i][j] == a[x][y]) g[i][j][k] = g[x][y][k] + 1;
        }
    }
    rFor (i, 2 * n - 1, 1) for (int j = br[i]; j >= bl[i]; j -= 2) {
        For (k, 3, 5) {
            int x = i + dx[k], y = j + dy[k];
            if (a[i][j] == a[x][y]) g[i][j][k] = g[x][y][k] + 1;
        }
    }
    For (i, 1, 2 * n - 1) for (int j = bl[i]; j <= br[i]; j += 2) {
        For (k, 0, 2) {
            int x = i + dx[k], y = j + dy[k];
            if (a[i][j] == a[x][y]) f[i][j][k] = min(f[x][y][k] + 1, g[i][j][k + 1]);
        }
    }
    rFor (i, 2 * n - 1, 1) for (int j = br[i]; j >= bl[i]; j -= 2) {
        For (k, 3, 5) {
            int x = i + dx[k], y = j + dy[k];
            if (a[i][j] == a[x][y]) f[i][j][k] = min(f[x][y][k] + 1, g[i][j][(k + 1) % 6]);
        }
    }
    For (i, 1, 2 * n - 1) for (int j = bl[i]; j <= br[i]; j += 2) {
        int x = n;
        For (k, 0, 5) cmin(x, f[i][j][k]);
        printf("%d%c", x, " \n"[j==br[i]]);
    }

    return 0;
}
