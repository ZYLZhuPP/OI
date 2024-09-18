#include<bits/stdc++.h>
using namespace std;

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

namespace Treap {
    struct Node {
        int l, r, s, v, heap;
        Node (int s = 0, int v = 0): s(s), v(v) { l = r = 0; heap = rand(); }
        bool operator < (const Node &x) const { return heap < x.heap; }
    };
    vector<Node > o(1);
    int tot = 0, rt = 0, x, y;
    int up(int u) { o[u].s = o[o[u].l].s + o[o[u].r].s + 1; return u; }
    void split_k(int p, int &u, int &v, int k) {
        if (!p) return void(u = v = 0);
        if (o[p].v < k) u = p, split_k(o[p].r, o[p].r, v, k);
        else v = p, split_k(o[p].l, u, o[p].l, k);
        up(p);
    }
    void split_r(int p, int &u, int &v, int k) {
        if (!p) return void(u = v = 0);
        if (o[o[p].l].s < k) u = p, split_r(o[p].r, o[p].r, v, k - o[o[p].l].s - 1);
        else v = p, split_r(o[p].l, u, o[p].l, k);
        up(p);
    }
    int merge(int u, int v) {
        if (!u || !v) return u + v;
        if (o[u] < o[v]) { o[u].r = merge(o[u].r, v); return up(u); }
        else { o[v].l = merge(u, o[v].l); return up(v); }
    }
    void ins(int k) {
        split_k(rt, rt, y, k);
        o.push_back(Node(1, k)), x = ++tot;
        rt = merge(rt, merge(x, y));
    }
    void del(int k) {
        split_k(rt, rt, x, k); split_k(x, x, y, k + 1);
        x = merge(o[x].l, o[x].r);
        rt = merge(rt, merge(x, y));
    }
    int rank(int k) {
        split_k(rt, rt, x, k); y = o[rt].s;
        rt = merge(rt, x);
        return y + 1;
    }
    int num(int k) {
        split_r(rt, rt, x, k - 1); split_r(x, x, y, 1);
        rt = merge(rt, merge(x, y));
        return o[x].v;
    }
    int pre(int k) {
        split_k(rt, rt, x, k);
        y = rt; while (o[y].r) y = o[y].r;
        rt = merge(rt, x);
        return o[y].v;
    }
    int suf(int k) {
        split_k(rt, rt, x, k + 1);
        y = x; while (o[y].l) y = o[y].l;
        rt = merge(rt, x);
        return o[y].v;
    }
}

int main() {
    int n;
    io >> n;
    while (n--) {
        int op, x;
        io >> op >> x;
        if (op == 1) Treap::ins(x);
        if (op == 2) Treap::del(x);
        if (op == 3) printf("%d\n", Treap::rank(x));
        if (op == 4) printf("%d\n", Treap::num(x));
        if (op == 5) printf("%d\n", Treap::pre(x));
        if (op == 6) printf("%d\n", Treap::suf(x));
    }

    return 0;
}
