#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;
ll Mo;
inline ll ml(const ll &x, const ll &y) { return x * y % Mo; }
inline void mul(ll &x, const ll &y) { x = ml(x, y); }

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

int T;
ll n, ans, inv[N];

int main() {
    io >> T;
    while (T--) {
        io >> n >> Mo;
        if (n >= Mo) { puts("0"); continue; }
        ll x = Mo - n;
        ans = n&1? 1: Mo - 1;
        inv[1] = 1;
        For (i, 2, x - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]), mul(ans, inv[i]);
        printf("%lld\n", ans);
    }

    return 0;
}
