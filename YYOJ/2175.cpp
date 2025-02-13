#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e9, M = 1e7 + 5;

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

unsigned x = 123456789, y = 362436069, z;
unsigned gen() {
	unsigned t;
	x ^= x << 16; x ^= x >> 5; x ^= x << 1;
	t = x; x = y; y = z; z = t ^ x ^ y;
	return z % N + 1;
}

int n, q, fa[M], l, r;
unsigned a[M];
ll res, ans;

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

int main() {
	io >> n >> q >> z;
	For (i, 1, n) a[i] = gen(), fa[i] = i;
    fa[n + 1] = n + 1;
	while (q--) {
		l = gen() % n + 1, r = gen() % n + 1;
		if (l > r) swap(l, r);
		res = 0; l = find(l);
        while (l <= r) {
            res += a[l];
            l = fa[l] = find(l + 1);
        }
		ans ^= res;
	}
	printf("%lld", ans);
	
	return 0;
}