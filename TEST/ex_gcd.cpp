#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

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

inline void ex_gcd(ll a, ll b, ll &x, ll &y, ll &g) { !b? x = 1, y = 0, g = a: (ex_gcd(b, a % b, y, x, g), y -= a / b * x); }

int main() {
    ll a, b, x, y, g;
    io >> a >> b;
    ex_gcd(a, b, x, y, g);
    printf("%lld %lld %lld", g, x, y);
    return 0;
}
