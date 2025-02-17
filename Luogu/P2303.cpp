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

ll n, ans;

int main() {
    io >> n; ans = n;
    for (ll i = 2; i * i <= n; ++i) if (!(n % i)) {
        int x = 0;
        while (!(n % i)) x++, n /= i;
        ans /= i;
        ans *= x * i - x + i;
    }
    if (n > 1) ans /= n, ans *= n + n - 1;
    printf("%lld", ans);

    return 0;
}
