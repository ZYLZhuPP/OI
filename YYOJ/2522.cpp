#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    bool operator ~ () const { return ~c; }
} io;

int T;
ll n, P, ans;

int main() {
    io >> T;
    while (T--) {
        io >> n >> P;
        ll x = n / P + 1;
        ans = x + 1;
        for (ll i = x; i >= 0 && i >= x - 2; i--) if (((i * P + 1) ^ (P - 1)) > n) ans--;
        printf("%lld\n", ans);
    }

    return 0;
}
