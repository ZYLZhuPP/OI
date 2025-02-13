#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

struct IO {
    int c, f;
#define gc() getchar()
	template<class C>
	inline IO& operator >> (C &x) {
    	x = 0; f = 1;
    	while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
    	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
    	x *= f; return *this;
	}
    inline bool operator ~ () { return ~c; }
} io;

int n, m, root = 1, rt[N], op;
ll x, y, z;

namespace Seg {
    struct Node {
        int l, r; ll v;
        Node(ll v = 0): v(v) { l = r = 0; }
    } o[N * 20];
    int tot, rub[N * 20], top;
    inline int node() { return top? rub[top--]: ++tot; }
    inline void del(int &p) { o[rub[++top] = p] = Node(); }
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].v = o[ls].v + o[rs].v; }
    inline void upd(int &p, int l, int r, int x, int v) {
        if (l > x || r < x) return;
        if (!p) p = node();
        if (l == r) return void(o[p].v += v);
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline ll query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p].v;
        M; return query(goL, x, y) + query(goR, x, y);
    }
    inline int kth(int p, int l, int r, int k) {
        if (l == r) return l;
        M; return o[ls].v>=k? kth(goL, k): kth(goR, k - o[ls].v);
    }
    inline int merge(int p, int l, int r, int q) {//merge q into p
        if (!p || !q) return p | q;
        if (l == r) { o[p].v += o[q].v; del(q); return p; }
        M; ls = merge(goL, o[q].l); rs = merge(goR, o[q].r); up(p);
        del(q); return p;
    }
    inline void split(int &p, int l, int r, int &q, int x, int y) {//move [x,y] in p to q
        if (!p || l > y || r < x) return;
        if (x <= l && r <= y) return swap(p, q);
        q = node();
        M; split(goL, o[q].l, x, y); split(goR, o[q].r, x, y); up(p); up(q);
    }
}
using namespace Seg;

int main() {
    io >> n >> m;
    For (i, 1, n)  io >> x, upd(rt[1], 1, n, i, x);
    while (m--) {
        io >> op;
        if (op == 0) {
            io >> x >> y >> z;
            split(rt[x], 1, n, rt[++root], y, z);
        } else if (op == 1) {
            io >> x >> y;
            rt[x] = merge(rt[x], 1, n, rt[y]);
        } else if (op == 2) {
            io >> x >> y >> z;
            upd(rt[x], 1, n, z, y);
        } else if (op == 3) {
            io >> x >> y >> z;
            printf("%lld\n", query(rt[x], 1, n, y, z));
        } else {
            io >> x >> y;
            printf("%d\n", o[rt[x]].v<y? -1: kth(rt[x], 1, n, y));
        }
    }

    return 0;
}
