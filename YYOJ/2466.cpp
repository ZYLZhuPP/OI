#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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

int T, n, swapCount, a[N];

namespace Seg {
    int mn[N << 2], mx[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { mn[p] = min(mn[ls], mn[rs]); mx[p] = max(mx[ls], mx[rs]); }
    inline void upd(int p, int l, int r, int x) {
        if (l > x || r < x) return;
        if (l == r) return mn[p] = mx[p] = a[x], void();
        M; upd(goL, x); upd(goR, x); up(p);
    }
    inline void build(int p, int l, int r) {
        if (l == r) return mn[p] = mx[p] = a[l], void();
        M; build(goL); build(goR); up(p);
    }
    inline int query_l(int p, int l, int r, int x, int w) {
        if (r < x || mx[p] < w) return -1;
        if (l == r) return l;
        M; int res = query_l(goL, x, w); return ~res? res: query_l(goR, x, w);
    }
    inline int query_r(int p, int l, int r, int x, int w) {
        if (l > x || mn[p] > w) return -1;
        if (l == r) return l;
        M; int res = query_r(goR, x, w); return ~res? res: query_r(goL, x, w);
    }
}
using namespace Seg;

int partition(int lo, int hi) {
    int pivot = a[(hi + lo) / 2];
    int i = lo - 1, j = hi + 1;
    while (true) {
        i = query_l(1, 1, n, i + 1, pivot);
        j = query_r(1, 1, n, j - 1, pivot);
        if (i >= j) return j;
        swap(a[i], a[j]); upd(1, 1, n, i); upd(1, 1, n, j);
        swapCount++;
    }
}

void quicksort(int lo, int hi) {
    if (lo >= hi) return;
    int p = partition(lo, hi);
    quicksort(lo, p);
    quicksort(p + 1, hi);
}

int main() {
    io >> T;
    while (T--) {
        swapCount = 0;
        io >> n;
        For (i, 1, n) io >> a[i];
        build(1, 1, n);
        quicksort(1, n);
        printf("%d\n", swapCount);
    }

    return 0;
}
