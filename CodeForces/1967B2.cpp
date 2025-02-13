#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e6 + 5;

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

int n, m, T, ans;

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n >> m;
        for (int i = 1 ; i * i <= n; ++i)
            for (int j = 1; j * j <= m; ++j) if (__gcd(i, j) == 1)
                ans += min(n / i, m / j) / (i + j);
        printf("%d\n", ans);
    }

    return 0;
}
