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

ll ans;
const int pri[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

inline ll mul(ll x, ll y, ll Mo) {
    ll r = x * y - Mo * ll(1.L / Mo * x * y);
    return r + Mo * ((r < 0) - (r >= Mo));
}

inline ll qPow(ll a, ll b, ll Mo) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mul(res, a, Mo);
        a = mul(a, a, Mo);
        b >>= 1;
    }
    return res;
}

inline bool Miller_Rabin(ll n) {
    for (int i = 0; i < 12; ++i)
        if (pri[i] == n) return 1;
    ll u = n - 1; u /= u & -u;
    for (int i = 0; i < 12; ++i) {
        ll a = pri[i], v = qPow(a, u, n);
        if (v == 1) continue;
        for (; v ^ n - 1 && u < n - 1; u <<= 1) 
            v = mul(v, v, n);
        if (u == n - 1) return 0;
    }
    return 1;
}

inline ll gcd(ll a, ll b) {
    if (!b) return a;
    return gcd(b, a % b);
}

ll Pollard_Rho(ll n) {
    if (!(n & 1)) return 2;
    auto f = [&](ll x) -> ll { return mul(x, x, n) + 1; };
    ll s = 0, t = 0, o = 0, M = 1, m, g;
    for (int i = 0; (i & 0xff) || (g = gcd(M, n)) == 1;
    ++i, s = f(s), t = f(f(t))) {
        if (s == t) s = ++o % n, t = f(s);
        m = mul(M, s - t + n, n);
        if (m) M = m;
    }
    return g;
}

void Divide(ll n) {
    if (n <= ans) return;
    if (Miller_Rabin(n)) ans = max(ans, n);
    else {
        ll m = n;
        while (!(n ^ m)) m = Pollard_Rho(n);
        while (!(n % m)) n /= m;
        Divide(m);
        if (n ^ 1) Divide(n);
    }
}

int T;
ll x;

int main() {
    io >> T;
    while (T--) {
        io >> x;
        if (Miller_Rabin(x)) puts("Prime");
        else {
            ans = 1;
            Divide(x);
            printf("%lld\n", ans);
        }
    }

    return 0;
}
