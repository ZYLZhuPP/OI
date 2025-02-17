#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 1e5 + 5, M = 5e5 + 5;
const lf inf = 1e9;

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

int n, m, l, r, x, pos[N];
lf val[M];

namespace Seg {
    struct Node {
        int v, id;
        Node(int v = 0, int id = 0): v(v), id(id) { }
        bool operator < (const Node &a) const { return v^a.v? val[v] < val[a.v]: id > a.id; }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define Mid int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = max(o[ls], o[rs]); }
    inline void upd(int p, int l, int r, int x, int v) {
        if (r < x || l > x) return;
        if (l == r) return void(o[p] = Node(v, x));
        Mid; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline Node query(int p, int l, int r, int x, int y) {
        if (r < x || l > y) return Node();
        if (x <= l && r <= y) return o[p];
        Mid; return max(query(goL, x, y), query(goR, x, y));
    }
#undef ls
#undef rs
}

struct P {
    int x, y;
    P(int x = 0, int y = 0): x(x), y(y) { }
    bool operator < (const P &a) const { return x^a.x? val[x] < val[a.x]: val[y] < val[a.y]; }
    bool operator == (const P &a) const { return x == a.x && y == a.y; }
} pp[M];

namespace SGT {
    const lf alp = 0.75;
    int rt, id[M], len, tot;
    struct Node {
        int l, r, sz; lf v;
        Node() { l = r = sz = v = 0; }
        Node(lf v): v(v) { l = r = 0; sz = 1; }
    } o[M];
#define ls o[p].l
#define rs o[p].r
    inline void up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; }
    inline void pia(int p) { if (!p) return; pia(ls); id[++len] = p; pia(rs); }
    inline void build(int &p, int l, int r, lf L, lf R) {
        if (l > r) return void(p = 0);
        Mid; p = id[m]; lf mid = (L + R) / 2; o[p] = Node(val[p] = mid);
        build(goL - 1, L, mid); build(goR, mid, R); up(p);
    }
    inline int ins(int &p, lf L, lf R, const P &v) {
        lf mid = (L + R) / 2;
        if (!p) return p = ++tot, o[p] = Node(val[p] = mid), pp[p] = v, p;
        if (pp[p] == v) return p;
        int res = v<pp[p]? ins(ls, L, mid, v): ins(rs, mid, R, v);
        up(p); if (max(o[ls].sz, o[rs].sz) > alp * o[p].sz) len = 0, pia(p), build(p, 1, len, L, R);
        return res;
    }
}

int main() {
    val[0] = -inf;
    io >> n >> m;
    SGT::ins(SGT::rt, 0, inf, P(0, 0));
    For (i, 1, n) Seg::upd(1, 1, n, i, pos[i] = 1);
    while (m--) {
        char op[2];
        scanf("%s", op);
        io >> l >> r;
        if (op[0] == 'C') {
            io >> x;
            Seg::upd(1, 1, n, x, pos[x] = SGT::ins(SGT::rt, 0, inf, P(pos[l], pos[r])));
        } else if (op[0] == 'Q') {
            printf("%d\n", Seg::query(1, 1, n, l, r).id);
        }
    }

    return 0;
}
