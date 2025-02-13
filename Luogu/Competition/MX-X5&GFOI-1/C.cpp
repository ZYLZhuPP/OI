#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

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

int T;
ll n, m;

int main() {
    io >> T;
    while (T--) {
        io >> n >> m;
        if (m % n) { puts("-1"); continue; }
        if (n == m) { puts("0"); continue; }
        m /= n; int x = 0;
        while (m > 1 && (n = __gcd(n, m)) > 1) m /= n, x++;
        if (m > 1) { puts("-1"); continue; }
        else printf("%d\n", 32 - __builtin_clz(x));
    }

    return 0;
}
