#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (register int i = (l); i <= (r); ++i)
const int N = 1e7 + 5, Mo = 1e9 + 7;
inline int mo(int &x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline int gmo(int x) { return mo(x); }
inline void add(int &x, const int &y) { mo(x += y); }
inline int mul(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, p[N], f[N];

int qPow(int a, int b) {
    int res = 1;
    do { if (~b&1 || (res = mul(res, a))) a = mul(a, a); } while (b >>= 1);
    return res;
}

void init() {
    p[0] = 1; int x = p[1] = qPow(2, n) - 1;
    For (i, 2, n) add(x, -1), p[i] = mul(p[i - 1], x);
}

int main() {
    io >> n;
    init();

    f[1] = f[2] = 0;
    For (i, 3, n) f[i] = gmo(p[i - 1] - gmo(f[i - 1] + mul(mul(i - 1, gmo(p[1] - i + 2)), f[i - 2])));

    printf("%d", gmo(p[n] - f[n]));

    return 0;
}
