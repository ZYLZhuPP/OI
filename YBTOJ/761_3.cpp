#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

namespace Seg {
    int tot;
    struct Node {
        int l, r, v;
        Node(int v = 0): v(v) { l = r = 0; }
    } o[N << 5];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline int copy(int p) { o[++tot] = o[p]; return tot; }
    inline void upd(int &p, int l, int r, const int &x, const int &v) {
        p = copy(p);
        if (l == r) return void(o[p].v = v);
        M; x<=m? upd(goL, x, v): upd(goR, x, v);
    }
    inline int query(int p, int l, int r, const int &x) {
        if (l == r) return o[p].v;
        M; return x<=m? query(goL, x): query(goR, x);
    }
}
using namespace Seg;

int n, m, rt[N];

int main() {
    io >> n >> m;
    int x, op, k, p;
    For (i, 1, n) io >> x, upd(rt[0], 1, n, i, x);
    For (i, 1, m) {
        io >> p >> op; rt[i] = rt[p];
        if (op == 1) {
            io >> k >> x;
            upd(rt[i], 1, n, k, x);
        } else if (op == 2) {
            io >> k;
            printf("%d\n", query(rt[i], 1, n, k));
        }
    }

    return 0;
}
