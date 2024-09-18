#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

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

int n, a, m, b;

inline int qPow(int a, int b, int p) {
    int r = 1;
    while (b) {
        if (b & 1) r = 1ll * r * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return r;
}

int main() {
    io >> a >> n;
    if (n == 1) return puts("0"), 0;
    int m = n, p = 1;
    for (int i = 2; i * i <= m; ++i) if (m % i == 0) {
        p *= i - 1; m /= i;
        while (m % i == 0) p *= i, m /= i;
    }
    if (m > 1) p *= m - 1;
    bool flag = 0;
    char c;
    while (!isdigit(c = gc()));
    while (isdigit(c)) {
        b = b * 10ll + (c ^ 48);
        if (b >= p) flag = 1, b %= p;
        c = gc();
    }
    if (flag) b += p;
    printf("%d", qPow(a, b, n));

    return 0;
}
