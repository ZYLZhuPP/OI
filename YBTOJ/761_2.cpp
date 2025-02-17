#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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
    inline bool operator ~ () const { return ~c; }
} io;

int n, rt[N];

namespace Treap {
    typedef int V;
    int tot, x, y;
    struct Node {
        int l, r, sz; V v; int heap;
        Node(): v(V()), heap(rand()) { l = r = sz = 0; }
        Node(V v): v(v), heap(rand()) { l = r = 0; sz = 1; }
    } o[N * 50];
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, o[v].l
#define goR rs, o[u].r, v
    int node(const V &v) { o[++tot] = Node(v); return tot; }
    int copy(int p) { o[++tot] = o[p]; return tot; }
    int up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; return p; }
    void split_k(int p, int &u, int &v, const V &k) {
        if (!p) return void(u = v = 0);
        if (o[p].v < k) u = copy(p), split_k(goR, k), up(u);
        else v = copy(p), split_k(goL, k), up(v);
    }
    void split_k_(int p, int &u, int &v, const V &k) {
        if (!p) return void(u = v = 0);
        if (!(k < o[p].v)) u = copy(p), split_k_(goR, k), up(u);
        else v = copy(p), split_k_(goL, k), up(v);
    }
    void split_r(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        if (o[ls].sz + 1 <= k) u = copy(p), split_r(goR, k - o[ls].sz - 1), up(u);
        else v = copy(p), split_r(goL, k), up(v);
    }
    int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].heap < o[v].heap) { u = copy(u); o[u].r = merge(o[u].r, v); return up(u); }
        else { v = copy(v); o[v].l = merge(u, o[v].l); return up(v); }
    }
    int size(int rt) { return o[rt].sz; }
    void ins(int &rt, const V &v) {
        split_k(rt, rt, y, v);
        x = node(v);
        rt = merge(rt, merge(x, y));
    }
    void del_all_k(int &rt, const V &v) {
        split_k(rt, rt, x, v); split_k_(x, x, y, v);
        rt = merge(rt, y);
    }
    void del_a_k(int &rt, const V &v) {
        split_k(rt, rt, x, v); split_k_(x, x, y, v);
        x = merge(o[x].l, o[x].r);
        rt = merge(rt, merge(x, y));
    }
    void del_r(int &rt, const int &l, const int &r) {
        split_r(rt, rt, x, l - 1); split_r(x, x, y, r - l + 1);
        rt = merge(rt, y);
    }
    void del_r(int &rt, const int &k) { del_r(rt, k, k); }
    int count(int rt, const V &l, const V &r) {
        split_k(rt, rt, x, l); split_k_(x, x, y, r);
        return o[x].sz;
    }
    int count(int rt, const V &v) { return count(rt, v, v); }
    int rnk(int rt, const V &v) {
        split_k(rt, x, y, v);
        return o[x].sz + 1;
    }
    V pre(int rt, const V &v) {
        split_k(rt, x, y, v);
        int p = x; while (rs) p = rs;
        return p? o[p].v: -INT_MAX;
    }
    V suf(int rt, const V &v) {
        split_k_(rt, x, y, v);
        int p = y; while (ls) p = ls;
        return p? o[p].v: INT_MAX;
    }
    const V kth(int rt, const int &k) {
        split_r(rt, rt, x, k - 1); split_r(x, x, y, 1);
        return o[x].v;
    }
}
using namespace Treap;

int main() {
    io >> n;
    For (i, 1, n) {
        int k, op, x;
        io >> k >> op >> x; rt[i] = rt[k];
        if (op == 1) ins(rt[i], x);
        else if (op == 2) del_a_k(rt[i], x);
        else if (op == 3) printf("%d\n", rnk(rt[i], x));
        else if (op == 4) printf("%d\n", kth(rt[i], x));
        else if (op == 5) printf("%d\n", pre(rt[i], x));
        else if (op == 6) printf("%d\n", suf(rt[i], x));
    }
    return 0;
}
