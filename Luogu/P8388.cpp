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

int n, a[N], f[N][N], g[N][N], ans;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) {
        int k = i, sj = 0, sk = 0, mx = g[i - 1][i - 1], cnt = 0;
        For (j, i, n) {
            g[i][j] = max(g[i - 1][j], f[i][j] = mx);
            sj += a[j]; while (k > 2 && sk < sj) sk += a[--k];
            if (sj == sk) cmax(mx, ++cnt + g[k - 1][i - 1]);
        }
        cmax(ans, f[i][n]);
    }
    printf("%d", ans);

    return 0;
}
