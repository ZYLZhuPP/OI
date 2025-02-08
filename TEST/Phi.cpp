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

int n, phi[N], pri[N], psz, mip[N];

inline ll Phi(ll x) {
    ll res = x;
    for (ll i = 2; i * i <= x; ++i) if (!(x % i)) {
        res = res / i * (i - 1);
        while (!(x % i)) x /= i;
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}

inline void init_Phi() {
    phi[1] = 1;
    For (i, 2, N - 1) {
        if (!mip[i]) {
            pri[mip[i] = ++psz] = i;
            phi[i] = i - 1;
        }
        For (j, 1, mip[i]) {
            int ne = i * pri[j];
            if (ne >= N) break;
            mip[ne] = j;
            if (j ^ mip[i]) phi[ne] = phi[i] * phi[pri[j]];
            else phi[ne] = phi[i] * pri[j];
        }
    }
}

int main() {
    ll x;
    io >> x;
    printf("%lld\n", Phi(x));
    io >> n;
    init_Phi();
    For (i, 1, n) printf("%d ", phi[i]);

    return 0;
}
