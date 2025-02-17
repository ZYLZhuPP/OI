#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, inf = 1e9;

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

namespace Treap {
    int rt, tot, rub[N], top;
    struct Node {
        int l, r, v, sz, s, t, rev; int heap;
        int mx, lm, rm;
        Node() { l = r = sz = s = t = rev = lm = rm = 0; mx = -inf; }
        Node(int v): v(v), heap(rand()) { l = r = t = rev = 0; sz = 1; s = mx = v; lm = rm = max(v, 0); }
    } o[N];
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, ls
#define goR rs, rs, v
    inline int newnode(const int &v) { int p = top? rub[top--]: ++tot; o[p] = Node(v); return p; }
    inline void del(int &p) { if (!p) return; del(ls); del(rs); rub[++top] = p; p = 0; }
    inline int up(int p) {
        o[p].s = o[ls].s + o[rs].s + o[p].v;
        o[p].sz = o[ls].sz + o[rs].sz + 1;
        o[p].mx = max(o[ls].rm + o[p].v + o[rs].lm, max(o[ls].mx, o[rs].mx));
        o[p].lm = max(o[ls].lm, o[ls].s + o[p].v + o[rs].lm);
        o[p].rm = max(o[rs].rm, o[rs].s + o[p].v + o[ls].rm);
        return p;
    }
    inline void rev(int p) { if (p) swap(ls, rs), swap(o[p].lm, o[p].rm), o[p].rev ^= 1; }
    inline void mark(int p, const int &x) { if (p) o[p].v = x, o[p].s = o[p].sz * x, o[p].mx = max(o[p].s, x), o[p].lm = o[p].rm = max(o[p].s, 0), o[p].t = 1; }
    inline void down(int p) { if (o[p].rev) rev(ls), rev(rs), o[p].rev = 0; if (o[p].t) mark(ls, o[p].v), mark(rs, o[p].v), o[p].t = 0; }
    inline void split_r(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        down(p);
        int x = o[ls].sz + 1;
        if (x <= k) u = p, split_r(goR, k - x);
        else v = p, split_r(goL, k);
        up(p);
    }
    inline int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].heap < o[v].heap) { down(u); o[u].r = merge(o[u].r, v); return up(u); }
        else { down(v); o[v].l = merge(u, o[v].l); return up(v); }
    }
}
using namespace Treap;

int T, n, m, k, x, u, v;
char op[20];

void solve() {
    del(rt);
    srand(13333);
    io >> n >> m;
    For (i, 1, n) io >> x, rt = merge(rt, newnode(x));
    while (m--) {
        scanf("%s", op);
        if (op[2] == 'S') {
            io >> k >> n;
            split_r(rt, u, rt, k);
            For (i, 1, n) io >> x, u = merge(u, newnode(x));
            rt = merge(u, rt);
        } else if (op[2] == 'L') {
            io >> k >> n;
            split_r(rt, rt, u, k - 1); split_r(u, u, v, n);
            del(u);
            rt = merge(rt, v);
        } else if (op[2] == 'K') {
            io >> k >> n >> x;
            split_r(rt, rt, u, k - 1); split_r(u, u, v, n);
            mark(u, x);
            rt = merge(rt, merge(u, v));
        } else if (op[2] == 'V') {
            io >> k >> n;
            split_r(rt, rt, u, k - 1); split_r(u, u, v, n);
            rev(u);
            rt = merge(rt, merge(u, v));
        } else if (op[2] == 'T') {
            io >> k >> n;
            split_r(rt, rt, u, k - 1); split_r(u, u, v, n);
            printf("%d\n", o[u].s);
            rt = merge(rt, merge(u, v));
        } else if (op[2] == 'X') {
            printf("%d\n", o[rt].mx);
        }
    }
}

int main() {
    io >> T;
    while (T--) solve();
    
    return 0;
}
//Luogu SP1470
