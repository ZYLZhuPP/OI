#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
const int N = 16, M = 1 << N;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
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

int n, S, x[N], y[N], z[N];
ll s[M];
lf g[N][N], mn[N][M], d[M], f[M];

int main() {
    freopen("desert.in", "r", stdin);
    freopen("desert.out", "w", stdout);
    io >> n; S = 1 << n;
    For (i, 0, n - 1) io >> x[i] >> y[i] >> z[i];
    For (i, 0, n - 1) For (j, 0, n - 1) g[i][j] = sqrt(1ll * (x[i] - x[j]) * (x[i] - x[j]) + 1ll * (y[i] - y[j]) * (y[i] - y[j]));
    For (i, 1, S - 1) {
        int x = __builtin_ctz(i);
        s[i] = s[i ^ (1 << x)] + z[x];
    }
    For (i, 0, n - 1) {
        mn[i][0] = 1e18;
        For (j, 1, S - 1) {
            int x = __builtin_ctz(j);
            mn[i][j] = min(mn[i][j ^ (1 << x)], g[i][x]);
        }
        mn[i][0] = 0;
    }
    For (i, 1, S - 1) d[i] = 1e18;
    For (i, 0, S - 1) For (j, 0, n - 1) if (!(i >> j & 1)) cmin(d[i | (1 << j)], d[i] + mn[j][i]);
    For (i, 1, S - 1) {
        int x = __builtin_popcount(i);
        f[i] = (s[i] - d[i]) / x;
    }
    For (i, 1, S - 1) for (int t = i; t; t = (t - 1) & i) cmax(f[i], min(f[t], f[i ^ t]));
    printf("%.10lf", f[S - 1]);

    fclose(stdin); fclose(stdout);
    return 0;
}
