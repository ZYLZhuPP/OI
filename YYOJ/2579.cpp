#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;
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
	inline bool operator ~ () const { return ~c; }
} io;

int T, n, K, g[N][N], f[N][N], pos[11];

int main() {
    io >> T;
    while (T--) {
        io >> n >> K;
        For (i, 1, n) {
            g[i][i] = 0;
            char c; while (!isdigit(c = gc()));
            while (isdigit(c)) g[i][i] |= 1 << (c ^ 48), c = gc();
        }
        For (i, 1, n) For (j, i + 1, n) g[i][j] = g[i][j - 1] | g[j][j];
        memset(f, 0, sizeof f);
        For (i, 1, n) {
            For (j, 1, 10) pos[j] = 0;
            For (j, 1, i) pos[__builtin_popcount(g[j][i])] = j;
            For (j, 1, 10) if (pos[j]) For (k, 1, K) cmax(f[i][k], f[pos[j] - 1][k - 1] + j);
        }
        printf("%d\n", f[n][K]);
    }

    return 0;
}
