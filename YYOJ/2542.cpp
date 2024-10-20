#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int n, a[N], b[N], c[N];
ll K, ans;

inline ll calc(ll x) {
    ll res = 0;
    For (i, 1, n) res += upper_bound(c + 1, c + n + 1, (x - a[i]) / b[i]) - c - 1;
    return res;
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) io >> b[i];
    For (i, 1, n) io >> c[i];
    sort(c + 1, c + n + 1);
    io >> K;
    ll l = 1, r = 1e18 + 1e9;
    while (l <= r) {
        ll m = (l + r) >> 1;
        if (calc(m) >= K) ans = m, r = m - 1;
        else l = m + 1;
    }
    printf("%lld", ans);

    return 0;
}
