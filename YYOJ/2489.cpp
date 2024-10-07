#include <bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int M = 305;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int m;
ll L, a[M << 1], s[M << 1], f[5 * M * M];

int main() {
	io >> m >> L;
	For (i, -m, m) io >> a[i + m];
	if (L < 0) L = -L, reverse(a, a + 2 * m + 1);

	ll v = L, cnt = 0;
	For (i, -m, m) {
		v -= 1ll * i * a[i + m];
		cnt += a[i + m];
		s[i + m] = a[i + m];
	}

	if (!v) return printf("%lld", cnt), 0;
	if (v < 0) {
		rFor (i, m, 1) {
			ll x = min(a[i + m], (-v) / i);
			s[i + m] -= x;
			cnt -= x;
			v += x * i;
			if (s[i + m]) break;
		}
	} else {
		For (i, -m, -1) {
			ll x = min(a[i + m], v / (-i));
			s[i + m] -= x;
			cnt -= x;
			v += x * i;
			if (s[i + m]) break;
		}
	}

	int maxV = m * (m + 1);
	if (abs(v) > maxV) return puts("impossible"), 0;

	auto update = [&](int a, int b)	{
		if (a > 0) rFor (V, maxV, a - maxV) cmax(f[V + maxV], f[V + maxV - a] + b);
		else For (V, -maxV, maxV + a) cmax(f[V + maxV], f[V + maxV - a] + b);
	};

	memset(f, 0xcf, sizeof f);
	f[maxV] = 0;

	For (i, -m, m) if (i) {
		if (s[i + m] ^ a[i + m]) {
			ll rem = a[i + m] - s[i + m];
			rem = min(rem, 2ll * maxV / abs(i));
			for (int c = 1; c <= rem; rem -= c, c <<= 1) update(c * i, c);
			if (rem) update(rem * i, rem);
		}

		if (s[i + m]) {
			ll rem = s[i + m];
			rem = min(rem, 2ll * maxV / abs(i));
			for (int c = 1; c <= rem; rem -= c, c <<= 1) update(-c * i, -c);
			if (rem) update(-rem * i, -rem);
		}
	}

	if (f[v + maxV] + cnt < 0) return puts("impossible"), 0;
	printf("%lld", f[v + maxV] + cnt);
	
	return 0;
}
