#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e3 + 5, M = 305, X = 55;

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

int n, m, x;
double h[M][N][X], g[M][N], f[M][N], p[N][M];

int main() {
    io >> n >> m;
    For (i, 1, n) For (j, 1, m) io >> x, p[i][j] = 1.l * x / 1000.l;

    For (i, 0, m) h[i][0][0] = 1;
    For (i, 1, m)
        For (j, 1, n) For (k, 0, X - 1)
            h[i][j][k] = (k? h[i][j - 1][k - 1] * p[j][i]: 0.l) + h[i][j - 1][k] * (1.l - p[j][i]);
    For (i, 1, m) For (j, 1, n) For (k, 0, X - 1) g[i][j] += min(j, k) * h[i][n][k];

    For (i, 1, m) For (j, 1, n)
        For (k, 0, min(j, X - 1))
            f[i][j] = max(f[i][j], f[i - 1][j - k] + g[i][k]);

    printf("%.12lf", f[m][n]);
    
    return 0;
}
