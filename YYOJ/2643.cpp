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

ll n, m;

int main() {
    io >> n >> m;
    if (!(n % m)) puts("0");
    else printf("%lld", 2 * ((n - m) / 2 % m));

    return 0;
}
