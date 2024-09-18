#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef long double Lf;
const int N = 1e6 + 5;

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

int n, x;
ll s[N], f[N], A, B, C;
int q[N];

inline ll dx(int i, int j) { return s[i] - s[j]; }
inline ll Y(int i) { return f[i] + A * s[i] * s[i] - B * s[i]; }
inline ll dy(int i, int j) { return  Y(i) - Y(j); }
inline Lf K(int i, int j) { return 1.L * dy(i, j) / dx(i, j); }
inline ll F(int i, int j) { return f[j] + A * (s[i] - s[j]) * (s[i] - s[j]) + B * (s[i] - s[j]) + C; }

int main() {
    io >> n;
    io >> A >> B >> C;
    For (i, 1, n) io >> x, s[i] = s[i - 1] + x;

    memset(f, -31, sizeof f); f[0] = 0;
    int h = 1, t = 0; q[++t] = 0;
    For (i, 1, n) {
        ll k = 2ll * A * s[i];
        while (h < t && K(q[h + 1], q[h]) >= k) h++;
        f[i] = F(i, q[h]);
        while (h < t && K(i, q[t]) >= K(q[t], q[t - 1])) t--;
        q[++t] = i;
    }
    printf("%lld", f[n]);

    return 0;
}
