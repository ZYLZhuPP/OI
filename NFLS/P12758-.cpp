#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const lf eps = 1e-10;
const int N = 505;

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

int n, m;
lf g[N][N], dis[N], a[N][N];

inline void Gauss() {
    For (i, 1, n) {
        int r = i;
        For (j, i + 1, n) if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        swap(a[i], a[r]);
        if (fabs(a[i][i]) < eps) continue;
        lf x = a[i][i];
        For (j, i, n + 1) a[i][j] /= x;
        For (j, 1, n) if (j ^ i){
            x = a[j][i];
            For (k, i, n + 1) a[j][k] -= a[i][k] * x;
        }
    }
}

int main() {
    freopen("snail.in", "r", stdin);
    freopen("snail.out", "w", stdout);
    io >> n >> m;
    For (i, 1, m) {
        For (j, 1, n) scanf("%lf", &g[i][j]);
        scanf("%lf", &dis[i]); dis[i] *= dis[i];
    }
    if (n == 2 && m <= 2) {
        if (m == 1) printf("%.10lf\n%.10lf", g[1][1] + sqrt(dis[1]), g[1][2]);
        else {
            lf x = 2 * (g[2][1] - g[1][1]), y = 2 * (g[1][2] - g[2][2]), z = dis[1] - dis[2] + g[2][1] * g[2][1] + g[2][2] * g[2][2] - g[1][1] * g[1][1] - g[1][2] * g[1][2];
            y /= x, z /= x;
            lf a = y * y + 1, b = 2 * (y * (z - g[1][1]) - g[1][2]), c = (z - g[1][1]) * (z - g[1][1]) + g[1][2] * g[1][2] - dis[1];
            lf Y = (-b + sqrt(b * b - 4 * a * c)) / (2 * a), X = y * Y + z;
            printf("%.10lf\n%.10lf", X, Y);
        }
        return 0;
    }
    For (i, 1, m) For (j, 1, n) dis[i] -= g[i][j] * g[i][j];
    For (i, 1, n) {
        For (j, 1, n) a[i][j] = 2 * (g[1][j] - g[i + 1][j]);
        a[i][n + 1] = dis[i + 1] - dis[1];
    }
    Gauss();
    For (i, 1, n) printf("%.10lf\n", a[i][n + 1]);
    
    fclose(stdin); fclose(stdout);
    return 0;
}
