#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, K, f[N][N][2], ans;

int main() {
    io >> n >> K;
    if (n <= 1) return printf("%d", n), 0;
    if (K == 1) return printf("%d", 6 * n - 12), 0;
    f[1][1][0] = 1;
    For (i, 1, n - 1) For (j, 1, K + 1) For (k, 0, 1) if (f[i][j][k]) {
        int x = f[i][j][k];
        if (k) {
            add(f[i + 1][j][1], x);
            add(f[i + 1][j + 1][1], x);
            add(f[i + 1][j + 2][0], ml(i - j - 1, x));
            add(f[i + 1][j + 1][0], ml(j, x));
        } else {
            add(f[i + 1][j][1], ml(2, x));
            add(f[i + 1][j + 2][0], ml(i - j, x));
            add(f[i + 1][j + 1][0], ml(j - 1, x));
        }
    }
    For (i, 1, K + 1) add(ans, mo(f[n][i][0] + f[n][i][1]));
    printf("%d", ans);

    return 0;
}
