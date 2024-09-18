#include<bits/stdc++.h>
using namespace std;

#define Fail return puts("-1"), 0;
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, c[N], f[N], ans, mx[N];

int main() {
    io >> n;
    For (i, 1, n) {
        int x, y;
        io >> x >> y;
        if (max(x, y) <= n || min(x, y) > n) Fail;
        if (x > y) swap(x, y), c[x] = 1;
        f[x] = y;
    }
    rFor (i, n, 1) mx[i] = max(mx[i + 1], f[i]);
    int m1, m2, t1, t2, c1, c2, mn;
    m1 = m2 = mn = 2 * n + 1, t1 = t2 = c1 = c2 = 0;
    For (i, 1, n) {
        if (f[i] < m1) m1 = f[i], t1++, c1 += c[i];
        else if (f[i] < m2) m2 = f[i], t2++, c2 += c[i];
        else Fail;
        cmin(mn, f[i]);
        if (mn > mx[i + 1]) {
            ans += min(c1 + t2 - c2, c2 + t1 - c1);
            m1 = m2 = 2 * n + 1, t1 = t2 = c1 = c2 = 0;
        }
    }
    printf("%d", ans);
    
    return 0;
}
