#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 6, M = 1e5 + 5;
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

int n, d[N], m[N], a[N], f[N][M], ans = 1e9;

int main() {
    freopen("dohnadohna.in", "r", stdin);
    freopen("dohnadohna.out", "w", stdout);
    io >> n;
    For (i, 1, 4) io >> d[i];
    For (i, 1, 5) io >> m[i];
    For (i, 1, n) io >> a[i];
    memset(f, 63, sizeof f);
    f[0][0] = 0;
    For (i, 1, 4) For (j, 0, 1e5) {
        cmin(f[i][j], f[i - 1][j]);
        if (j + d[i] <= 1e5) cmin(f[i][j + d[i]], f[i][j] + m[i]);
    }
    For (i, 1, 4) rFor (j, 1e5, 1) cmin(f[i][j], f[i][j + 1]);
    For (i, 0, 3) {
        int res = i * m[5];
        For (j, 1, n) if (a[j] > i * 40000) res += f[j][a[j] - i * 40000];
        cmin(ans, res);
    }
    printf("%d", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}