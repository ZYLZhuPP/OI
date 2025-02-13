#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
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

int T, n, m, a[N][2], g[N][2], f[N][2], ans;

inline void solve() {
    io >> n >> m;
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    For (i, 1, n) io >> a[i][0] >> a[i][1], f[i][0] = f[i][1] = 1, g[i][1] = 1;
    For (i, 2, n) {
        For (j, 1, i - 1) {
            For (k, 0, 1) For (l, 0, 1) if (a[i][k] > a[j][l]) {
                if (cmax(f[i][k], f[j][l] + 1)) g[i][k] = g[j][l] + k;
                else if (f[i][k] == f[j][l] + 1) cmin(g[i][k], g[j][l] + k);
            }
        }
    }
    ans = 0;
    For (i, 1, n) For (j, 0, 1) cmax(ans, f[i][j] - max(0, g[i][j] - m));
    printf("%d\n", ans);
}

int main() {
    io >> T;
    while (T--) solve();

    return 0;
}
