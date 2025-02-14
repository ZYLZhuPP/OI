#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, Mo = 998244353;
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

int n, a[N], inv[N], p[N][N], f[N][N][2], g[N][N];

int main() {
    freopen("tournament.in", "r", stdin);
    freopen("tournament.out", "w", stdout);
    io >> n;
    inv[1] = 1; For (i, 2, n) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    For (i, 1, n) io >> a[i], f[i][i][0] = f[i][i][1] = 1;
    For (i, 1, n) For (j, 1, n) if (i ^ j) p[i][j] = ml(a[i], qPow(a[i] + a[j], Mo - 2));
    For (len, 2, n) {
        For (l, 1, n - len + 1) {
            int r = l + len - 1;
            For (k, l, r - 1) add(g[l][r], ml(f[l][k][0], f[k + 1][r][1]));
            For (k, l + 1, r) add(f[l][r][0], ml(f[k][r][0], ml(p[l][k], g[l][k])));
            For (k, l, r - 1) add(f[l][r][1], ml(f[l][k][1], ml(p[r][k], g[k][r])));
            mul(f[l][r][0], inv[len - 1]); mul(f[l][r][1], inv[len - 1]);
        }
    }
    For (i, 1, n) printf("%d\n", ml(f[1][i][1], f[i][n][0]));

    fclose(stdin); fclose(stdout);
    return 0;
}
