#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, inf = 1e9;

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

int n, m;

namespace Seg {
    struct Node { int l, r, sz; } o[N * 60];
    int rt[N], tot;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline int copy(int p) { o[++tot] = o[p]; return tot; }
    inline void upd(int &p, int l, int r, int x) {
        if (l > x || r < x) return;
        p = copy(p); o[p].sz++;
        if (l == r) return;
        M; upd(goL, x); upd(goR, x);
    }
    inline int count(int p, int l, int r, int q, int x, int y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y ) return o[q].sz - o[p].sz;
        M; return count(goL, o[q].l, x, y) + count(goR, o[q].r, x, y);
    }
    int kth(int p, int l, int r, int q, int k) {
        if (l == r) return l;
        int x = o[o[q].l].sz - o[ls].sz;
        M; return k<=x? kth(goL, o[q].l, k): kth(goR, o[q].r, k - x);
    }
}
using namespace Seg;

int main() {
    io >> n >> m;
    int x, l, r, k;
    For (i, 1, n) io >> x, upd(rt[i] = rt[i - 1], 0, inf, x);
    while (m--) {
        io >> l >> r >> k;
        printf("%d\n", kth(rt[l - 1], 0, inf, rt[r], k));
    }

    return 0;
}
