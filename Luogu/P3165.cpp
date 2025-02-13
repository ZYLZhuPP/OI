#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef pair<int, int > P;
const int N = 1e5 + 5, inf = 1e9;

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

int n;

namespace Treap {
    struct Node {
        bool rev; int l, r, sz, heap; P v, mn;
        Node() { rev = l = r = sz = 0; v = mn = {inf, inf}; }
        Node(P v): v(v), mn(v), heap(rand()) { rev = l = r = 0; sz = 1; }
    } o[N];
    int tot, rt, x, y;
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, o[v].l
#define goR rs, o[u].r, v
    inline int up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; o[p].mn = min(o[p].v, min(o[ls].mn, o[rs].mn)); return p; }
    inline void rev(int p) { if (p) o[p].rev ^= 1, swap(ls, rs); }
    inline void down(int p) { if (o[p].rev) rev(ls), rev(rs), o[p].rev = 0; }
    inline void split_r(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        down(p);
        if (o[ls].sz + 1 <= k) u = p, split_r(goR, k - o[ls].sz - 1), up(u);
        else v = p, split_r(goL, k), up(v);
    }
    inline int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].heap < o[v].heap) return down(u), o[u].r = merge(o[u].r, v), up(u);
        else return down(v), o[v].l = merge(u, o[v].l), up(v);
    }
    inline void ins(const P &v) {
        o[++tot] = Node(v);
        rt = merge(rt, tot);
    }
    inline void reverse(const int &k) {
        split_r(rt, x, y, k);
        rev(x);
        rt = merge(x, y);
    }
    inline int rnk(int p) {
        if (o[p].v == o[p].mn) return o[ls].sz + 1;
        down(p);
        return o[ls].mn==o[p].mn? rnk(ls): (o[ls].sz + 1 + rnk(rs));
    }
}
using namespace Treap;

int main() {
    srand(time(0));
    io >> n;
    int x;
    For (i, 1, n) io >> x, ins({x, i});
    For (i, 1, n) {
        int x = rnk(rt);
        printf("%d%c", i + x - 1, " \n"[i==n]);
        reverse(x);
        split_r(rt, x, rt, 1);
    }

    return 0;
}
