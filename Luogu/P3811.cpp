#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e6 + 5;
int Mo;
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, inv[N];

int main() {
    io >> n >> Mo;
    inv[1] = 1;
    For (i, 2, n) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    For (i, 1, n) printf("%d\n", inv[i]);

    return 0;
}
