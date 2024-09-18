#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5;

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

int n, m, inf, a[N], b[N << 1], l[N], r[N], v[N], op[N];

namespace Treap {
    int tot, x, y;
    struct Node {
        int l, r, sz; int v; int heap;
        Node() { l = r = sz = 0; }
        Node(int v): v(v), heap(rand()) { l = r = 0; sz = 1; }
    } o[N << 8];
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, o[v].l
#define goR rs, o[u].r, v
    inline int up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; return p; }
    inline void split_k(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        if (o[p].v < k) u = p, split_k(goR, k), up(u);
        else v = p, split_k(goL, k), up(v);
    }
    inline void split_k_(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        if (!(k < o[p].v)) u = p, split_k_(goR, k), up(u);
        else v = p, split_k_(goL, k), up(v);
    }
    inline int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].heap < o[v].heap) { o[u].r = merge(o[u].r, v); return up(u); }
        else { o[v].l = merge(u, o[v].l); return up(v); }
    }
    inline void ins(int &rt, const int &v) {
        split_k(rt, rt, y, v);
        x = ++tot, o[x] = Node(v);
        rt = merge(rt, merge(x, y));
    }
    inline void del(int &rt, const int &v) {
        split_k(rt, rt, x, v); split_k_(x, x, y, v);
        x = merge(o[x].l, o[x].r);
        rt = merge(rt, merge(x, y));
    }
    inline int count(int &rt, const int &l, const int &r) {
        split_k(rt, rt, x, l); split_k_(x, x, y, r);
        int res = o[x].sz;
        rt = merge(rt, merge(x, y));
        return res;
    }
#undef ls
#undef rs
#undef goL
#undef goR
}

namespace Seg {
    int rt[N << 3];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void ins(int p, int l, int r, const int &x, const int &v) {
        if (l > x || r < x) return;
        Treap::ins(rt[p], v);
        if (l == r) return;
        M; ins(goL, x, v); ins(goR, x, v);
    }
    inline void del(int p, int l, int r, const int &x, const int &v) {
        if (l > x || r < x) return;
        Treap::del(rt[p], v);
        if (l == r) return;
        M; del(goL, x, v); del(goR, x, v);
    }
    inline int rnk(int p, int l, int r, const int &x, const int &y, const int &v) {
        if (l > v) return 0;
        if (r < v) return Treap::count(rt[p], x, y);
        if (l == r) return 0;
        M; return rnk(goL, x, y, v) + rnk(goR, x, y, v);
    }
    inline int kth(int p, int l, int r, const int &x, const int &y, const int &k) {
        if (l == r) return l;
        int s = Treap::count(rt[ls], x, y);
        M; return k<=s? kth(goL, x, y, k): kth(goR, x, y, k - s);
    }
}
using namespace Seg;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], b[++inf] = a[i];
    For (i, 1, m) {
        io >> op[i];
        if (op[i] == 3) io >> l[i] >> v[i];
        else io >> l[i] >> r[i] >> v[i];
        if (op[i] ^ 2) b[++inf] = v[i];
    }
    sort(b + 1, b + inf + 1); inf = unique(b + 1, b + inf + 1) - b - 1;
    For (i, 1, n) a[i] = lower_bound(b + 1, b + inf + 1, a[i]) - b;
    For (i, 1, m) if (op[i] ^ 2) v[i] = lower_bound(b + 1, b + inf + 1, v[i]) - b;

    For (i, 1, n) ins(1, 1, inf, a[i], i);
    For (i, 1, m) {
        if (op[i] == 1) {
            printf("%d\n", rnk(1, 1, inf, l[i], r[i], v[i]) + 1);
        } else if (op[i] == 2) {
            printf("%d\n", b[kth(1, 1, inf, l[i], r[i], v[i])]);
        } else if (op[i] == 3) {
            del(1, 1, inf, a[l[i]], l[i]);
            ins(1, 1, inf, a[l[i]] = v[i], l[i]);
        } else if (op[i] == 4) {
            int k = rnk(1, 1, inf, l[i], r[i], v[i]);
            printf("%d\n", k? b[kth(1, 1, inf, l[i], r[i], k)]: -INT_MAX);
        } else if (op[i] == 5) {
            int k = rnk(1, 1, inf, l[i], r[i], v[i] + 1);
            printf("%d\n", l[i]+k<=r[i]? b[kth(1, 1, inf, l[i], r[i], k + 1)]: INT_MAX);
        }
    }

    return 0;
}
