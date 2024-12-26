#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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

int n, q, cnt[105], psz;
ll pri[105], s[N];
vector<ll > sta;
unordered_map<ll, int > f;

inline void init(int k, ll x) {
    if (k == psz) return sta.pb(x);
    For (i, 1, cnt[k]) x *= pri[k];
    rFor (i, cnt[k], 0) init(k + 1, x), x /= pri[k];
}

int main() {
    io >> n;
    ll x;
    For (i, 1, n) io >> x, s[i] = s[i - 1] + x;
    x = s[n];
    For (i, 2, 1e6) {
        if (!(x % i)) pri[psz++] = i;
        while (!(x % i)) cnt[psz - 1]++, x /= i;
    }
    if (x <= 1e12) {
        if (x > 1) pri[psz++] = x, cnt[psz - 1] = 1;
        init(0, 1);
        For (i, 1, n) f[__gcd(s[i], s[n])]++;
        For (i, 0, psz - 1) for (auto &x : sta) if (x <= s[n] / pri[i] && f.count(x * pri[i])) f[x] += f[x * pri[i]];
    }
    io >> q;
    while (q--) {
        io >> x;
        if (s[n] % x) { puts("-1"); continue; }
        if (!f.count(x)) {
            int c = 0;
            For (i, 1, n) c += !(s[i] % x);
            f[x] = c;
        }
        printf("%lld\n", s[n] / x + n - 2 * f[x]);
    }

    return 0;
}
