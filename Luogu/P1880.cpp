#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 205;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, mn[N][N], mx[N][N], s[N];

int main() {
    memset(mn, 31, sizeof mn);
    io >> n;
    int x;
    For (i, 1, n) io >> x, s[i] = s[i - 1] + x;
    For (i, 1, n) s[n + i] = s[n] + s[i], mn[i][i] = mn[n + i][n + i] = 0;
    For (len, 2, n) {
        For (l, 1, 2 * n - len + 1) {
            int r = l + len - 1;
            For (k, l, r - 1) cmin(mn[l][r], mn[l][k] + mn[k + 1][r] + s[r] - s[l - 1]), cmax(mx[l][r], mx[l][k] + mx[k + 1][r] + s[r] - s[l - 1]);
        }
    }
    rFor (i, n, 1) cmin(mn[i][i + n - 1], mn[i + 1][i + n]), cmax(mx[i][i + n - 1], mx[i + 1][i + n]);
    printf("%d\n%d", mn[1][n], mx[1][n]);

    return 0;
}
