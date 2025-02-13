#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef __int128 lll;
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

int T, n, m;
ll b[N], p[N], w[N], a[N], mx, x;

inline void ex_gcd(ll a, ll b, ll &x, ll &y, ll &g) { !b? x = 1, y = 0, g = a: (ex_gcd(b, a % b, y, x, g), y -= a / b * x); }

inline ll solve() {
    ll A = 0, P = 1;
    For (i, 1, n) {
        ll x, y, g;
        ex_gcd(a[i], p[i], x, y, g);
        if (b[i] % g) return -1;
        b[i] /= g; p[i] /= g;
        a[i] = ((lll)x * b[i] % p[i] + p[i]) % p[i];
        A -= a[i];
        ex_gcd(p[i], P, x, y, g);
        if (A % g) return -1;
        A /= g; P = (lll)p[i] * P / g;
        x = ((lll)x * A % P + P) % P;
        A = (((lll)x * p[i] + a[i]) % P + P) % P;
    }
    if (A < mx) A += ((mx - A - 1) / P + 1) * P;
    return A + (A < mx? P: 0);
}

int main() {
    io >> T;
    while (T--) {
        mx = 0;
        io >> n >> m;
        multiset<ll > se;
        For (i, 1, n) io >> b[i];
        For (i, 1, n) io >> p[i];
        For (i, 1, n) io >> w[i];
        For (i, 1, m) io >> x, se.insert(x);
        For (i, 1, n) {
            auto it = se.upper_bound(b[i]);
            if (it != se.begin()) it--;
            a[i] = *it; se.erase(it);
            se.insert(w[i]);
            mx = max(mx, (b[i] - 1) / a[i] + 1);
        }
        printf("%lld\n", solve());
    }

    return 0;
}
