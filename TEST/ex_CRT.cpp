#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef __int128 lll;
const int N = 1e5 + 5;

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

int n;
ll b[N], p[N], a[N];

inline void ex_gcd(ll a, ll b, ll &x, ll &y, ll &g) { !b? x = 1, y = 0, g = a: (ex_gcd(b, a % b, y, x, g), y -= a / b * x); }

inline ll ex_CRT() {
    ll A = 0, P = 1, x, y, g;
    For (i, 1, n) {
        A -= a[i];
        ex_gcd(p[i], P, x, y, g);
        if (A % g) return -1;
        x = ((lll)x * (A / g) % P + P) % P;
        P *= p[i] / g;
        A = (((lll)x * p[i] + a[i]) % P + P) % P;
    }
    return A;
}

int main() {
    io >> n;
    For (i, 1, n) io >> p[i] >> a[i];
    printf("%lld", ex_CRT());

    return 0;
}
