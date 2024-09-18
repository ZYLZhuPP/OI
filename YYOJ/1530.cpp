#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e7 + 5;
const ll Mo = 998244353;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

ll n, m, k, ans;
ll fac[N], invfac[N];

ll C(ll n, ll m) {
    if (m < 0 || n < m) return 0;
    if (!m) return 1;
    if (n <= N) return fac[n] * invfac[n - m] % Mo * invfac[m] % Mo;
    ll res = 1;
    for (ll i = n; i > n - m; i--) res = (i % Mo * res) % Mo;
    return res * invfac[m] % Mo;
}

ll qPow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % Mo;
        a = (a * a) % Mo;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = invfac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = (fac[i - 1] * i) % Mo;
    invfac[N - 1] = qPow(fac[N - 1], Mo - 2);
    for (int i = N - 2; i >= 0; i--) invfac[i] = (invfac[i + 1] * (i + 1)) % Mo;
}

int main() {
    io >> n >> m >> k;
    init();

    ll r = n % m;
    for (ll sum = r; sum <= k * (m - 1) && sum <= n; sum += m) {
        ll res = 0;
        for (ll i = 0; i <= k; i++) {
            if (sum - i * (m - 1) < k) break;
            ll w = (C(sum - i * (m - 1) - 1, k - 1) * C(k, i)) % Mo;
            res = (res + ((i&1)? -1: 1) * w + Mo) % Mo;
        }
        res = (res * C((n - sum) / m + k - 1, k - 1)) % Mo;
        ans = (ans + res) % Mo;
    }

    printf("%lld", ans);

    return 0;
}
