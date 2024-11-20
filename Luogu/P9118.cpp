#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef long double Lf;

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
int K;
unordered_map<ll, bool > mp;

int main() {
    io >> n >> K;
    if (K == 1) return printf("%lld", n), 0;
    if (K == 2) ans = floor(sqrt(Lf(n))); else ans = 1;
    For (k, max(3, K), 60) {
        For (i, 2, 1e6) {
            if ((ll)round(pow(Lf(i), k / 2)) > n / (ll)round(pow(Lf(i), k - k / 2))) break;
            ll x = (ll)round(pow(Lf(i), k / 2)) * (ll)round(pow(Lf(i), k - k / 2));
            if (K == 2) {
                ll y = sqrt(x);
                if (y * y == x) continue;
            }
            if (!mp[x]) ans += mp[x] = 1;
        }
    }
    printf("%lld", ans);

    return 0;
}
