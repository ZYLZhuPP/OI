#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, a[N], l, r;

namespace Splay {
    int rt;
    struct Node {
        int f, c[2], v, sz, rev;
        Node() { f = c[0] = c[1] = v = sz = rev = 0; }
        Node(int v, int f = 0): f(f), v(v) { sz = 1; c[0] = c[1] = rev = 0; }
    } o[N];
#define fu o[u].f
#define ls o[u].c[0]
#define rs o[u].c[1]
    inline bool is(int u) { return o[fu].c[1] == u; }
    inline void up(int u) { if (u) o[u].sz = o[ls].sz + o[rs].sz + 1; }
    inline void rev(int u) { if (u) swap(ls, rs), o[u].rev ^= 1; }
    inline void down(int u) { if (o[u].rev) rev(ls), rev(rs), o[u].rev = 0; }
    inline void rot(int u) {
        int k = is(u), f = fu, ff = o[f].f, c = o[u].c[!k];
        if (ff) o[ff].c[is(f)] = u; o[u].c[!k] = f; o[f].c[k] = c;
        if (c) o[c].f = f; o[f].f = u; fu = ff;
        up(f); up(u);
    }
    inline void splay(int u, int g = 0) { for (; fu ^ g; rot(u)) if (o[fu].f ^ g) rot(is(fu)^is(u)? u: fu); if (!g) rt = u; }
    int build(int l = 1, int r = n, int f = 0) {
        if (l > r) return 0;
        int m = (l + r) >> 1, u = m; o[u] = Node(a[m], f);
        ls = build(l, m - 1, u); rs = build(m + 1, r, u); up(u);
        return u;
    }
    inline int kth(int u, int k) {
        down(u);
        if (o[ls].sz >= k) return kth(ls, k);
        else { k -= o[ls].sz + 1; return k? kth(rs, k): (splay(u), u); }
    }
}
using namespace Splay;

int main() {
    io >> n >> m;
    For (i, 1, n) a[i] = i;
    rt = build();
    while (m--) {
        io >> l >> r;
        if (l == 1 && r == n) rev(rt);
        else if (l == 1) {
            int u = kth(rt, r + 1);
            rev(ls);
        } else if (r == n) {
            int u = kth(rt, l - 1);
            rev(rs);
        } else {
            int u = kth(rt, l - 1), v = kth(rt, r + 1);
            splay(u, v); rev(rs);
        }
    }
    For (i, 1, n) printf("%d ", o[kth(rt, i)].v);

    return 0;
}
