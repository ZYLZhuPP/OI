#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 205;

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

int n, m;
long double dv[N], f[2][N], ans;

int main() {
    io >> n >> m;
    dv[0] = 1; For (i, 1, n) dv[i] = dv[i - 1] / m;
    
    f[1][0] = 1;
    For (i, 1, n) For (j, 0, i - 1)
        f[1][i] += f[0][j] * (i - j) * dv[i - j],
        f[0][i] += (f[0][j] * (m - 2) + f[1][j] * (m - 1)) * (i - j) * dv[i - j];

    ans = dv[n] * n * m;
    For (i, 1, n - 1) For (j, 0, n - i - 1)
        ans += dv[i + j] * (i + j) * m * f[0][n - i - j];

    printf("%.5Lf", ans);

    return 0;
}
