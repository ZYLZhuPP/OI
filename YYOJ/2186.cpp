#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef array<int, 2 > P;
const int N = 5e5 + 5, inf = 1e9;
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
	int st[66], t;
#define pc(c) putchar(c)
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) st[++t] = x % 10, x /= 10;
        while (t) pc(st[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (const char &c) {
    	pc(c); return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int T, n, a[N], mx;
P b[N];

namespace Seg {
	struct mat {
		int o[2][2];
		mat(int o00 = inf, int o01 = inf, int o10 = inf, int o11 = inf) { o[0][0] = o00; o[0][1] = o01; o[1][0] = o10; o[1][1] = o11; }
		mat operator * (const mat &a) const {
			mat r;
			For (k, 0, 1) For (i, 0, 1) For (j, 0, 1) cmin(r.o[i][j], o[i][k] + a.o[k][j]);
			return r;
		}
	};
	struct Node {
		int sz; mat v;
	} o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
	inline void up(int p) { o[p].sz = o[ls].sz + o[rs].sz; o[p].v = o[ls].v * o[rs].v; }
	inline void build(int p, int l, int r) {
		o[p].sz = 0; o[p].v = mat(0, inf, inf, 0);
		if (l == r) return;
		M; build(goL); build(goR);
	}
	inline void upd(int p, int l, int r, int x) {
		if (l > x || r < x) return;
		if (l == r) return o[p].sz = 1, o[p].v = mat(1, inf, b[x][0], 0), void();
		M; upd(goL, x); upd(goR, x); up(p);
	}
	inline P find(int p, int l, int r, int x) {
		if (l == r) return {l, x};
		M; return b[m][0]<x-o[ls].sz? find(goR, x - o[ls].sz): find(goL, x);
	}
	inline mat query(int p, int l, int r, int x, int y) {
		if (x <= l && r <= y) return o[p].v;
		M; return y<=m? query(goL, x, y): x>m? query(goR, x, y): (query(goL, x, y) * query(goR, x, y));
	}
}
using namespace Seg;

int main() {
	io >> T;
	while (T--) {
		mx = 0;
		io >> n;
		build(1, 1, n);
		For (i, 1, n) io >> a[i], b[i] = {a[i], i};
		sort(b + 1, b + n + 1);
		For (i, 1, n) a[i] = lower_bound(b + 1, b + n + 1, P{a[i], i}) - b;
		For (i, 1, n) {
			upd(1, 1, n, a[i]);
			//cerr << o[1].v.o[0][0] << endl;
			mx = max(mx, a[i]);
			if (b[mx][0] <= -i) { io << -i << '\n'; continue; }
			P x = find(1, 1, n, 0);
			//cerr << x[0] << " " << x[1] << endl;
			mat y = query(1, 1, n, x[0], n);
			//cerr << y.o[0][0] << " " << y.o[1][0] << endl;
			io << min(x[1] + y.o[0][0], y.o[1][0])  << '\n';
		}
	}
	
	return 0;
} 
