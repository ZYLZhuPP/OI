#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define mkp make_pair
#define st first
#define nd second
const int N = 1e5 + 5;

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

namespace tr {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int i, int v) { for (; i < N; i += lowbit(i)) o[i] = max(o[i], v); }
    inline int pre(int i) { int r = 0; for (; i; i -= lowbit(i)) r = max(r, o[i]); return r; }
}

int w, n, t, p, v, p1[N], p2[N], m;
pair<int, pair<int, int > > a[N];

int main() {
    io >> w >> n;
    For (i, 1, n) {
        io >> t >> p >> v;
        p1[i] = p - 2 * t;
        p2[i] = p + 2 * t;
        a[i] = mkp(-p1[i], mkp(p2[i], v));
    }
    sort(p2 + 1, p2 + n + 1); m = unique(p2 + 1, p2 + n + 1) - p2 - 1;

    sort(a + 1, a + n + 1);
    For (i, 1, n) {
        int p = a[i].nd.st, v = a[i].nd.nd;
        p = lower_bound(p2 + 1, p2 + m + 1, p) - p2;
        tr::upd(p, tr::pre(p) + v);
    }
    printf("%d", tr::pre(N - 1));

    return 0;
}
