#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define ckmin(x, y) ((x)>(y)? (x)=(y), 1: 0)
typedef long long ll;
const int N = 55;

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
	inline bool operator ~ () {return ~c;}
} io;

int n, w[N];
ll a, b, d[N], f[N][N][N][N], g[N][N];

int main() {
    io >> n >> a >> b;
    For (i, 1, n) io >> w[i], d[i] = w[i];
    sort(d + 1, d + n + 1);
    For (i, 1, n) w[i] = lower_bound(d + 1, d + n + 1, w[i]) - d;

    memset(f, 31, sizeof f); memset(g, 31, sizeof g);
    For (i, 1, n) f[i][i][w[i]][w[i]] = 0, g[i][i] = a;

    For (len, 1, n) {
        For (l, 1, n - len + 1) {
            int r = l + len - 1;
            For (x, 1, n) {
                For (y, x, n) {
                    ckmin(f[l][r][min(x, w[r])][max(y, w[r])], f[l][r - 1][x][y]);
                    For (i, l, r) ckmin(f[l][r][x][y], f[l][i - 1][x][y] + g[i][r]);
                }
            }

            For (x, 1, n) For (y, x, n)
                ckmin(g[l][r], f[l][r][x][y] + a + b * (d[y] - d[x]) * (d[y] - d[x]));
        }
    }

    printf("%lld", g[1][n]);

    return 0;
}
