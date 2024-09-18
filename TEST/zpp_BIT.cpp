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
	inline bool operator ~ () { return ~c; }
} io;

int n, m;

namespace BIT {
    int L[N], R[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) {
        for (int l = x - 1; l; l -= lowbit(l)) L[l] += d;
        for (int r = x; r < N; r += lowbit(r)) R[r] += d;
    }
    inline int query(int l, int r) {
        int res = 0;
        for (l--; l && l + lowbit(l) <= r; l += lowbit(l)) res += L[l];
        for (; r && r - lowbit(r) >= l; r -= lowbit(r)) res += R[r];
        return res;
    }
}
using namespace BIT;

int main() {
    io >> n >> m;
    int x;
    For (i, 1, n) io >> x, upd(i, x);
    while (m--) {
        int op, x, d, l, r;
        io >> op;
        if (op == 1) io >> x >> d, upd(x, d);
        else if (op == 2) io >> l >> r, printf("%d\n", query(l, r));
    }

    return 0;
}
