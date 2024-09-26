#include"expr.h"
#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e4 + 5;

int rt[N], tim;

namespace Treap {
    struct Node { bool rev; int l, r, op, sz; Data s; } o[N * 2000];
    int tot;
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, o[v].l
#define goR rs, o[u].r, v
    inline int copy(int p) { o[++tot] = o[p]; return tot; }
    inline int up(int p) {
        o[p].sz = o[ls].sz + o[rs].sz + 1; 
        if (ls && rs) o[p].s = F(o[ls].s, o[rs].s, o[p].op);
        else if (ls || rs) o[p].s = o[ls|rs].s;
        return p;
    }
    inline void rev(int &p) { if (p) p = copy(p), swap(ls, rs), o[p].rev ^= 1; }
    inline void down(int p) { if (o[p].rev) rev(ls), rev(rs), o[p].rev = 0; }
    inline void split(int p, int &u, int &v, int k) {
        if (!p) return void(u = v = 0);
        p = copy(p); down(p);
        if (o[ls].sz + 1 <= k) u = p, split(goR, k - o[ls].sz - 1), up(u);
        else v = p, split(goL, k), up(v);
    }
    inline int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].op < o[v].op || (o[u].op == o[v].op && rand() % (o[u].sz + o[v].sz) < o[u].sz)) return u = copy(u), down(u), o[u].r = merge(o[u].r, v), up(u);
        else return v = copy(v), down(v), o[v].l = merge(u, o[v].l), up(v);
    }
}
using namespace Treap;

void init(int test_id, int n, int m, int k, const Data *a, const int *ops) {
    srand(time(0));
    rFor (i, n - 1, 0) {
        o[++tot] = {0, 0, 0, 101, 1, a[i]}, rt[0] = merge(tot, rt[0]);
        if (i) o[++tot] = {0, 0, 0, ops[i], 1, {0}}, rt[0] = merge(tot, rt[0]);
    }
}

Data modify_data(int id, int pos, Data v) {
    int x, y, z; split(rt[id], x, y, pos << 1); split(y, y, z, 1);
    o[++tot] = {0, 0, 0, 101, 1, v}; rt[++tim] = merge(x, merge(tot, z));
    return o[rt[tim]].s;
}

Data modify_op(int id, int pos, int new_op) {
    int x, y, z; split(rt[id], x, y, pos * 2 - 1); split(y, y, z, 1);
    o[++tot] = {0, 0, 0, new_op, 1, {0}}; rt[++tim] = merge(x, merge(tot, z));
    return o[rt[tim]].s;
}

Data reverse(int id, int l, int r) {
    int x, y, z; split(rt[id], y, z, r << 1 | 1); split(y, x, y, l << 1);
    rev(y); rt[++tim] = merge(x, merge(y, z));
    return o[rt[tim]].s;
}
