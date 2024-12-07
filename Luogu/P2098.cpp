#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, Mo = 1e9 + 9;

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

int n, m, K, a[N], b[N], f[N][N][11];

int main() {
    io >> n >> m >> K;
    For (i, 1, n) io >> a[i];
    For (i, 1, m) io >> b[i];
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    For (i, 0, n) For (j, 0, m) f[i][j][0] = 1;
    For (k, 1, K) {
        For (i, 1, n) For (j, 1, m) if (a[i] > b[j]) f[i][j][k] = f[i - 1][j - 1][k - 1];
        For (i, 1, n) For (j, 1, m) (f[i][j][k] += f[i][j - 1][k]) %= Mo;
        For (i, 1, n) For (j, 1, m) (f[i][j][k] += f[i - 1][j][k]) %= Mo;
    }
    printf("%d", f[n][m][K]);

    return 0;
}
