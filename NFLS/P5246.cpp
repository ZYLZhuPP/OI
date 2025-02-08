#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 405;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int T, a[N];
ll fac[N], f[N][N], g[N];
array<ll, 2 > h[N];

struct P {
    ll x, y;
    P(const ll &x, const ll &y): x(x), y(y) { }
    inline bool operator < (const P &a) const { return 1.L * x / y < 1.L * a.x / a.y; }
    inline void out() const {
        ll g = __gcd(x, y);
        printf("%lld/%lld\n", x / g, y / g);
    }
};

int main() {
    freopen("line.in", "r", stdin);
    freopen("line.out", "w", stdout);
    f[1][0] = fac[1] = 1;
    For (i, 2, 16) fac[i] = fac[i - 1] * i;
    For (i, 1, 15) For (j, 0, i * (i - 1) / 2) For (k, 0, i) f[i + 1][j + k] += f[i][j];
    io >> T;
    while (T--) {
        int n, A, B, C, D;
        io >> n >> A >> B >> C >> D;
        int m = n * (n - 1) / 2;
        For (i, 0, m) g[i] = min(i * A, (m - i) * A + B);
        For (i, 0, m) h[i] = {g[i], f[n][i]};
        sort(h, h + m + 1);
        ll s = 0, cnt = 0; P mn(h[m][0], 1);
        For (i, 0, m - 1) s += h[i][0] * h[i][1], cnt += h[i][1], cmin(mn, P(s + fac[n] * C, cnt));
        while (D--) {
            int x = 0;
            For (i, 1, n) io >> a[i];
            For (i, 1, n) For (j, i + 1, n) x += a[i] > a[j];
            min(P(g[x], 1), mn).out();
        }
    }

    fclose(stdin); fclose(stdout);
    return 0;
}