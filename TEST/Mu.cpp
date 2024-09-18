#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

struct IO {
	char c; int f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, mu[N], pri[N], psz, mip[N];

int Mu(ll x) {
    int res = 1;
    for (ll i = 2; i * i <= x; ++i) if (!(x % i)) {
        res = -res;
        if (!((x /= i) % i)) return 0;
    }
    if (x > 1) res = -res;
    return res;
}

void init_Mu() {
    mu[1] = 1;
    For (i, 2, N - 1) {
        if (!mip[i]) {
            pri[mip[i] = ++psz] = i;
            mu[i] = -1;
        }
        For (j, 1, mip[i]) {
            int ne = i * pri[j];
            if (ne >= N) break;
            mip[ne] = j;
            if (j ^ mip[i]) mu[ne] = -mu[i];
            else mu[ne] = 0;
        }
    }
}

int main() {
    ll x;
    io >> x;
    printf("%d\n", Mu(x));
    io >> n;
    init_Mu();
    For (i, 1, n) printf("%d ", mu[i]);

    return 0;
}
