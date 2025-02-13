#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }

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

int n, m, a[N], b[N], lst[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int v) { for (; x <= m; x += lowbit(x)) add(o[x], v); }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) add(r, o[x]); return r; }
}
using namespace BIT;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1); m = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, n) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
    memset(lst, -1, sizeof lst);
    For (i, 1, n) {
        int x = query(a[i] - 1);
        upd(a[i], mo(x - lst[a[i]]));
        lst[a[i]] = x;
    }
    printf("%d", mo(query(m) - m));

    return 0;
}
