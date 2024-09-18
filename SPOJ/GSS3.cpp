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

int n, m, a[N];

namespace Seg {
    struct Node {
        int s, mx, l, r;
        Node operator + (const Node &a) const {
            return Node{s + a.s, max(max(mx, a.mx), r + a.l), max(l, s + a.l), max(a.r, a.s + r)};
        }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] + o[rs]; }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p] = Node{a[l], a[l], a[l], a[l]}, void();
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x, const int &v) {
        if (l > x || r < x) return;
        if (l == r) return o[p] = Node{v, v, v, v}, void();
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline Node query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return o[p];
        M; return y<=m? query(goL, x, y): x>m? query(goR, x, y): (query(goL, x, y) + query(goR, x, y));
    }
}
using namespace Seg;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    build(1, 1, n);
    io >> m;
    int op, x, y;
    while (m--) {
        io >> op >> x >> y;
        if (op == 0) upd(1, 1, n, x, y);
        else if (op == 1) printf("%d\n", query(1, 1, n, x, y).mx);
    }

    return 0;
}
//Luogu SP1716