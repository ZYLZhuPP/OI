#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 10005, M = 1005, Mo = 1e9 + 7;
inline int mo(int &x) { return x -= x>=Mo? Mo: 0; }
inline int gmo(int x) { return mo(x); }
inline void add(int &x, int y) { mo(x += y); }

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

int n, K, m, lim, h, ans, C[N][M], f[15][N];

void init() {
    C[0][0] = 1;
    For (i, 1, 10000) {
        C[i][0] = 1;
        For (j, 1, 1000) C[i][j] = gmo(C[i - 1][j - 1] + C[i - 1][j]);
    }
}

int main() {
    io >> n >> K >> m; lim = n - K; h = K >> 1;
    init();

    f[0][0] = 1;
    For (i, 0, 13) {
        int o = (1 << i) * (m + 1);
        For (j, 0, lim) if (f[i][j]) {
            for (int k = 0; k * (m + 1) <= h && k * o + j <= lim; ++k) 
                add(f[i + 1][j + k * o], 1ll * f[i][j] * C[h][k * (m + 1)] % Mo);
        }
    }

    For (i, 0, lim) add(ans, 1ll * f[14][i] * C[n - i - h][h] % Mo);
    printf("%d", gmo(C[n][K] - ans + Mo));

    return 0;
}
