#include<bits/stdc++.h>
using namespace std;

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

int T, n;

int main() {
    T = 10;
    while (T--) {
        io >> n;
        if (n <= 2) printf("%d\n", n + 1);
        else if (n & 1) printf("%lld\n", 1ll * ((n + 1) / 2) * ((n + 1) / 2 + 1) + 1);
        else printf("%lld\n", 1ll * n / 2 * (n / 2 + 2) + 1);
    }

    return 0;
}
