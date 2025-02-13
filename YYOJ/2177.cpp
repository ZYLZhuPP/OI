#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, K, C[N][N], h[N], f[N], ans;

inline void init() {
    For (i, 0, n) C[i][0] = 1;
    For (i, 1, n) For (j, 1, i) C[i][j] = mo(C[i - 1][j] + C[i - 1][j - 1]);
    For (i, 0, n) h[i] = qPow(2, C[i][2]);
}

int main() {
    io >> n >> K;
    init();
    For (k, 1, K) {
        For (i, k + 1, n) {
            f[i] = ml(C[i - 1][k], h[i - 1]);
            For (j, k + 1, i - 1) add(f[i], -ml(C[i - 1][j - 1], ml(f[j], h[i - j])));
        }
        add(ans, f[n]);
    }
    printf("%d", ans);

    return 0;
}
