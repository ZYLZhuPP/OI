#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int n, c[4], d[4], s;
ll ans, f[N];

int main() {
    For (i, 0, 3) io >> c[i];
    io >> n;
    f[0] = 1;
    For (i, 0, 3) For (j, c[i], N - 1) f[j] += f[j - c[i]];
    while (n--) {
        ans = 0;
        For (i, 0, 3) io >> d[i];
        io >> s;
        For (j, 0, 15) {
            int sign = 1, x = s;
            For (i, 0, 3) if (j >> i & 1) x -= c[i] * (d[i] + 1), sign = -sign;
            if (x >= 0) ans += sign * f[x];
        }
        printf("%lld\n", ans);
    }

    return 0;
}
