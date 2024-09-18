#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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
	inline bool operator ~ () const { return ~c; }
} io;

int n, m;
ll f[N], ans;

int main() {
    io >> n >> m;
    rFor (i, min(n, m), 1) {
        f[i] = 1ll * (n / i) * (m / i);
        for (int j = i << 1; j <= min(n, m); j += i) f[i] -= f[j];
        ans += (i * 2 - 1) * f[i];
    }
    printf("%lld", ans);

    return 0;
}
