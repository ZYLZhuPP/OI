#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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
	inline bool operator ~ () { return ~c; }
} io;

int T, n, V, ans, g[N], f[N];

inline void solve() {
    ans = 0;
    memset(f, 0, sizeof f);
    io >> V >> n;
    while (n--) {
        int v, a, b;
        io >> v >> a >> b;
        For (i, v, V) g[i] = f[i - v] + a + b;
        For (i, 2 * v, V) cmax(g[i], g[i - v] + a);
        For (i, v, V) cmax(f[i], g[i]);
    }
    For (i, 0, V) cmax(ans, f[i]);
    printf("%d\n", ans);
}

int main() {
    io >> T;
    while (T--) solve();

    return 0;
}
