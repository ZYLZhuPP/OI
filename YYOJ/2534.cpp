#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

inline void out(ll a, ll b) {
    if (!(a % b)) return printf("%lld", a / b), void();
    ll g = __gcd(a, b);
    printf("%lld/%lld", a / g, b / g);
}

int n, x;
ll s, m;

int main() {
    io >> n;
    For (i, 1, n) {
        io >> x;
        s += x; m += x * x;
        printf("%lld ", s);
        out(s, i); putchar(' ');
        out(i * m - s * s, 1ll * i * i); putchar('\n');
    }

    return 0;
}
