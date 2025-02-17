#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e6 + 5;

struct IO {
    int c, f;
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

ll T, n, pri[N], psiz, mu[N], mip[N], sum_mu[N];
unordered_map<ll, ll > mp_mu;

ll S_mu(ll n) {
    if (n < N) return sum_mu[n];
    if (mp_mu[n]) return mp_mu[n];
    ll res = 1;
    for (ll i = 2, j; i <= n; i = j + 1) {
        j = n / (n / i);
        res -= S_mu(n / i) * (j - i + 1);
    }
    return mp_mu[n] = res;
}

ll S_phi(ll n) {
    ll res = 0;
    for (ll i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        res += (S_mu(j) - S_mu(i - 1)) * (n / i) * (n / i);
    }
    return (res - 1) / 2 + 1;
}

void init() {
    mu[1] = 1;
    For (i, 2, N - 1) {
        if (!mip[i]) pri[mip[i] = ++psiz] = i, mu[i] = -1;
        For (j, 1, mip[i]) {
            if (i * pri[j] >= N) break;
            if (j ^ mip[i]) mu[i * pri[j]] = -mu[i];
            else mu[i * pri[j]] = 0;
            mip[i * pri[j]] = j;
        }
    }
    For (i, 1, N - 1) sum_mu[i] = sum_mu[i - 1] + mu[i];
}

int main() {
    init();
    io >> T;
    while (T--) {
        io >> n;
        printf("%lld %lld\n", S_phi(n), S_mu(n));
    }

    return 0;
}
