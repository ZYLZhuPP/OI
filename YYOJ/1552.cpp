#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;
const ll Mo = 1e9 + 7;

struct IO {
	char c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

ll n, k, ans, inv[N], fac[N], invfac[N], f[N], g;

void init() {
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; ++i) inv[i] = (Mo - Mo / i) * inv[Mo % i] % Mo;
    fac[0] = invfac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % Mo, invfac[i] = invfac[i - 1] * inv[i] % Mo;
}

int main() {
    io >> n >> k;
    init();

    ans = f[0] = 1;
    for (int i = 1; i < n; ++i) {
        if (i - k - 1 >= 0) g = (g - f[i - k - 1] * invfac[i - k - 1] + Mo) % Mo;
        g = (g + f[i - 1] * invfac[i - 1]) % Mo;
        f[i] = g * fac[i - 1] % Mo;
        ans = (ans + invfac[i] * f[i]) % Mo;
    }
    ans = ans * fac[n - 1] % Mo;
    ans = (fac[n] - ans + Mo) % Mo;

    printf("%lld", ans);

    return 0;
}
