#include<bits/stdc++.h>
using namespace std;

#define Fail { puts("Impossible"); exit(0); }
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e3 + 5, inf = 1e9;
int Mo;
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, mx, b[N], p[N], a[N];

inline int ex_BSGS(int &a) {
    int A = 1, b = 1, c = 0, g;
    while ((g = __gcd(a, Mo)) > 1) {
        if (b % g) return -1;
        b /= g, Mo /= g, mul(A, a / g), c++;
        if (A == b) return c;
    }
    unordered_map<int, int > mp;
    int B = ceil(sqrt(Mo)), x = 1;
    For (i, 0, B - 1) mp[ml(b, x)] = i + 1, mul(x, a);
    int y = A;
    For (i, 1, B) { mul(y, x); if (mp[y]) return i * B - mp[y] + c + 1; }
    return -1;
}

inline int ex_BSGS(int &a, int &b) {
    if (Mo == 1) return 0;
    b %= Mo; if (!a) return !b? 0: -1; else if (b == 1) return 0;
    a %= Mo; if (!a) return !b? 1: -1;
    int A = 1, c = 0, g;
    while ((g = __gcd(a, Mo)) > 1) {
        if (b % g) return -1;
        b /= g, Mo /= g, mul(A, a / g), c++;
        if (A == b) return c;
    }
    unordered_map<int, int > mp;
    int B = ceil(sqrt(Mo)), x = 1;
    For (i, 1, B) mul(x, a), mp[ml(b, x)] = i;
    int y = A;
    For (i, 1, B) { mul(y, x); if (mp[y]) return i * B - mp[y] + c; }
    return -1;
}

inline void ex_gcd(ll a, ll b, ll &x, ll &y, ll &g) { !b? x = 1, y = 0, g = a: (ex_gcd(b, a % b, y, x, g), y -= a / b * x); }

inline ll ex_CRT() {
    ll A = 0, P = 1, x, y, g;
    For (i, 1, n) {
        if (P > inf) { if (A < a[i] || (A - a[i]) % p[i]) Fail else continue; }
        A -= a[i];
        ex_gcd(p[i], P, x, y, g);
        if (A % g) Fail;
        x = (x * (A / g) % P + P) % P;
        P *= p[i] / g;
        A = ((x * p[i] + a[i]) % P + P) % P;
    }
    if (A < mx) A += ((mx - A - 1) / P + 1) * P;
    if (A > inf) Fail;
    return A;
}

int main() {
    io >> n;
    int X = -1;
    For (i, 1, n) {
        int x, y;
        io >> x >> Mo >> y;
        a[i] = ex_BSGS(x, y);
        if (!~a[i]) Fail;
        mx = max(mx, a[i]);
        Mo /= __gcd(Mo, y);
        p[i] = ex_BSGS(x);
        if (!~p[i]) X = a[i];
    }
    if (~X) {
        For (i, 1, n) {
            if (~p[i] && (X < a[i] || (X - a[i]) % p[i])) Fail;
            if (!~p[i] && X ^ a[i]) Fail;
        }
        printf("%d", X);
        return 0;
    }
    printf("%lld", ex_CRT());

    return 0;
}
