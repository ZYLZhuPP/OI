#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5005, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }

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

int n, K, f[N][N], s[N], ans;

int main() {
    io >> n >> K;
    f[1][1] = 1;
    For (i, 2, n) f[2][n] = 1;
    For (i, 2, n) s[i] = s[i - 2] + 1;
    For (i, 3, K) {
        For (j, i, n) f[i][j] = mo(s[j - 1] + s[j - i + 1]);
        memset(s, 0, sizeof s);
        s[1] = f[i][1];
        For (j, 2, n) s[j] = mo(s[j - 2] + f[i][j]);
    }
    For (i, 1, K) add(ans, ml(K - i + 1, 2 * f[i][n]));
    printf("%d", ans);

    return 0;
}
