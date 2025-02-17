#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e4 + 5, Mo = 1e9 + 7;
inline int mo(const ll &x) { return (x + Mo) % Mo; }
inline void add(int &x, const int &y) { x = mo(x + y); }

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
    mt19937 rnd(time(0));
    int tot, x, y;
    struct Node {
        bool rev; short v, L, R, mx; int l, r, sl, sr, cl, cr, heap; ll sz, c;
        Node() { sz = 0; mx = -1; }
        Node(short v): v(v), heap(rnd()) {
            l = r = sl = sr = cl = cr = rev = 0;
            mx = L = R = v; sz = c = 1;
        }
        void reset() { sl = sr = cl = cr = 0; mx = L = R = v; sz = c = 1; }
    } o[N * 190];
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, o[v].l
#define goR rs, o[u].r, v
    inline int node(const short &v) { o[++tot] = Node(v); return tot; }
    inline int copy(const int &p) { o[++tot] = o[p]; return tot; }
    inline int up(const int &p) {
        int l = ls, r = rs; ll v = o[p].v;
        o[p].reset();
        if (l) {
            o[p].L = o[l].L;
            if (o[l].R > v) add(o[p].cl, 1), add(o[p].sl, mo(o[r].sz + 2));
            if (o[l].R < v) add(o[p].cr, 1), add(o[p].sr, mo(o[l].sz + 1));
            if (o[l].mx > o[p].mx) o[p].mx = o[l].mx, o[p].c = o[l].c;
            else o[p].c += (o[l].mx == o[p].mx) * o[l].c;
            o[p].sz += o[l].sz;
            add(o[p].cl, o[l].cl); add(o[p].cr, o[l].cr);
            add(o[p].sl, mo(o[l].sl + 1ll * mo(o[r].sz + 1) * o[l].cl));
            add(o[p].sr, o[l].sr);
        }
        if (r) {
            o[p].R = o[r].R;
            if (o[r].L > v) add(o[p].cr, 1), add(o[p].sr, mo(o[l].sz + 2));
            if (o[r].L < v) add(o[p].cl, 1), add(o[p].sl, mo(o[r].sz + 1));
            if (o[r].mx > o[p].mx) o[p].mx = o[r].mx, o[p].c = o[r].c;
            else o[p].c += (o[r].mx == o[p].mx) * o[r].c;
            o[p].sz += o[r].sz;
            add(o[p].cl, o[r].cl); add(o[p].cr, o[r].cr);
            add(o[p].sl, o[r].sl);
            add(o[p].sr, mo(o[r].sr + 1ll * mo(o[l].sz + 1) * o[r].cr));
        }
        return p;
    }
    inline void rev(int &p) { if (p) p = copy(p), swap(ls, rs), swap(o[p].L, o[p].R), swap(o[p].cl, o[p].cr), swap(o[p].sl, o[p].sr), o[p].rev ^= 1; }
    inline void down(const int &p) { if (o[p].rev) rev(ls), rev(rs), o[p].rev = 0; }
    inline void split_r(int p, int &u, int &v, const ll &k) {
        if (!p) return void(u = v = 0);
        down(p);
        if (o[ls].sz + 1 <= k) u = copy(p), split_r(goR, k - o[ls].sz - 1), up(u);
        else v = copy(p), split_r(goL, k), up(v);
    }
    inline void split_m(int p, int &u, int &v, const short &mx, const ll &k) {
        if (!p) return void(u = v = 0);
        down(p);
        ll x = (o[ls].mx == mx) * o[ls].c + (o[p].v == mx);
        if (x < k) u = copy(p), split_m(goR, mx, k - x), up(u);
        else v = copy(p), split_m(goL, mx, k), up(v);
    }
    inline int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].heap < o[v].heap || (o[u].heap == o[v].heap && o[u].sz > o[v].sz)) { u = copy(u); down(u); o[u].r = merge(o[u].r, v); return up(u); }
        else { v = copy(v); down(v); o[v].l = merge(u, o[v].l); return up(v); }
    }
    inline void ins(int &rt, const ll &k, const int &x) {
        split_r(rt, rt, y, k);
        rt = merge(rt, merge(x, y));
    }
    inline void rev(int &rt, const ll &l, const ll &r) {
        split_r(rt, rt, x, l - 1); split_r(x, x, y, r - l + 1);
        rev(x);
        rt = merge(rt, merge(x, y));
    }
    inline int query(int rt, const ll &l, const ll &r) {
        split_r(rt, x, rt, l - 1); split_r(rt, rt, y, r - l + 1);
        split_m(rt, x, y, o[rt].mx, (o[rt].c + 1) >> 1);
        return mo(o[x].sl + o[y].sr - o[y].cr);
    }
}
using namespace Treap;

int rt[N];

int main() {
    //srand(time(0));
    int n, m = 0;
    io >> n;
    int x; ll k, l, r;
    while (n--) {
        char op[2];
        scanf("%s", op);
        if (op[0] == 'I') {
            io >> x >> k;
            m++;
            ins(rt[m] = rt[m - 1], k, node(x));
        } else if (op[0] == 'R') {
            io >> l >> r;
            m++;
            rev(rt[m] = rt[m - 1], l, r);
        } else if (op[0] == 'M') {
            io >> x >> k;
            m++;
            ins(rt[m] = rt[m - 1], k, rt[x]);
        } else if (op[0] == 'Q') {
            io >> l >> r;
            printf("%d\n", query(rt[m], l, r));
        }
    }

    return 0;
}
