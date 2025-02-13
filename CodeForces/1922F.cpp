#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105, inf = 1e9;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () { return ~c; }
} io;

int T, n, m, f[N][N][N], g[N][N][N], ans;

int main() {
    io >> T;
    while (T--) {
        io >> n >> m;
        For (i, 1, n) For (j, i, n) For (k, 1, m) f[i][j][k] = g[i][j][k] = inf;
        int x;
        For (i, 1, n) {
            io >> x;
            For (j, 1, m) f[i][i][j] = j!=x, g[i][i][j] = j==x;
        }
        For (len, 2, n) {
            For (l, 1, n - len + 1) {
                int r = l + len - 1;
                For (i, 1, m) {
                    For (k, l, r - 1) {
                        cmin(f[l][r][i], f[l][k][i] + f[k + 1][r][i]);
                        cmin(g[l][r][i], g[l][k][i] + g[k + 1][r][i]);
                    }
                    For (j, 1, m) cmin(g[l][r][j], g[l][r][i] + 1);
                }
                For (i, 1, m) cmin(f[l][r][i], g[l][r][i] + 1);
            }
        }
        ans = inf;
        For (i, 1, m) cmin(ans, f[1][n][i]);
        printf("%d\n", ans);
    }

    return 0;
}
