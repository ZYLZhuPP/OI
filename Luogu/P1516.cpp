#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

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

ll n, m, c, x, y, l, d, a, b, g;

inline void ex_gcd(ll a, ll b, ll &x, ll &y, ll &g) {
    if (!b) return x = 1, y = 0, g = a, void();
    ex_gcd(b, a % b, y, x, g);
    y -= a / b * x;
}

int main(){
    io >> x >> y >> n >> m >> l;
    if (n > m) swap(n, m), swap(x, y);
    ex_gcd(m - n, l, a, b, d);
    l /= d;
    if ((x - y) % d != 0 || m == n) puts("Impossible");
    else printf("%lld",(a * (x - y) / d % l + l) % l);
}