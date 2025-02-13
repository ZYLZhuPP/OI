#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const lf eps = 1e-8;
const int N = 2e3 + 5;

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
    inline IO& operator >> (double &x){
		double p(1); x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
		if (!(c ^ 46)) while (isdigit(c = gc())) x += (c ^ 48) * (p /= 10);
		x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, ans;
bitset<N > g[N];

int main() {
    io >> n;
    For (i, 1, n) For (j, 1, n) {
        lf x;
        io >> x;
        if (x > eps) g[i][j] = 1;
    }
    For (i, 1, n) For (j, 1, n) if (g[j][i]) g[j] |= g[i];
    For (i, 1, n) g[i][i] = 1;
    For (i, 1, n) ans += g[i].count();
    printf("%d", ans);

    return 0;
}
