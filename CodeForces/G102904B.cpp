#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;
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

int n, K, l, r, a[N];
ll res, f[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x <= n; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

inline ll get(int x, int y) {
    while (x < l) l--, res += query(a[l]), upd(a[l], 1);
    while (y > r) r++, res += r - l - query(a[r]), upd(a[r], 1);
    while (x > l) upd(a[l], -1), res -= query(a[l]), l++;
    while (y < r) upd(a[r], -1), res -= r - l - query(a[r]), r--;
    return res;
}

inline void solve(int x, int y, int l, int r) {
    if (l > r) return;
    int m = (l + r) >> 1, z = x; ll mn = 1e18;
    For (i, x, y) if (cmin(mn, f[i] + get(i + 1, m) + K)) z = i;
    cmin(f[m], mn);
    solve(x, z, l, m - 1); solve(z, y, m + 1, r);
}

inline void cdq(int l, int r) {
    if (l == r) return;
    int m = (l + r) >> 1;
    cdq(l, m); solve(l, m, m + 1, r); cdq(m + 1, r);
}

int main() {
    io >> n >> K;
    For (i, 1, n) io >> a[i];
    memset(f, 63, sizeof f); f[0] = 0;
    l = 1, r = 0;
    cdq(0, n);
    printf("%lld", f[n]);

    return 0;
}
