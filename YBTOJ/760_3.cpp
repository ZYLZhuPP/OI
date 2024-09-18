#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef unsigned long long ull;
const int N = 1e5 + 5;
const ull __ = 131;

ull _[N];
int n, m, x, y;
char s[N], op[2];

namespace Treap {
    int rt, tot;
    struct Node {
        int l, r, sz; ull v, s; int heap;
        Node() { l = r = sz = v = s = 0; }
        Node(ull v): v(v), heap(rand()) { l = r = 0; sz = 1; s = v; }
    } o[N];
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, ls
#define goR rs, rs, v
    inline int up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; o[p].s = o[ls].s + _[o[ls].sz] * (o[p].v + __ * o[rs].s); return p; }
    inline void split_r(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        if (o[ls].sz + 1 <= k) u = p, split_r(goR, k - o[ls].sz - 1);
        else v = p, split_r(goL, k);
        up(p);
    }
    inline int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].heap < o[v].heap) { o[u].r = merge(o[u].r, v); return up(u); }
        else { o[v].l = merge(u, o[v].l); return up(v); }
    }
}
using namespace Treap;

inline void upd(const int &k, const ull &v) {
    split_r(rt, rt, x, k - 1); split_r(x, x, y, 1);
    o[x] = Node(v);
    rt = merge(rt, merge(x, y));
}

inline void ins(const int &k, const ull &v) {
    split_r(rt, rt, y, k);
    o[x = ++tot] = Node(v);
    rt = merge(rt, merge(x, y));
}

inline ull get(const int &k, const int &len) {
    split_r(rt, rt, x, k - 1); split_r(x, x, y, len);
    ull res = o[x].s;
    rt = merge(rt, merge(x, y));
    return res;
}

inline int LCP(int x, int y) {
    int res = 0;
    rFor (i, 16, 0) {
        int len = 1 << i;
        if (max(x, y) + len - 1 <= tot && get(x, len) == get(y, len))
            res |= len, x += len, y += len;
    }
    return res;
}

void init() { srand(time(0)); _[0] = 1; For (i, 1, N - 1) _[i] = _[i - 1] * __; }

int main() {
    init();
    scanf("%s", s); n = strlen(s);
    For (i, 0, n - 1) ins(i, s[i]);
    scanf("%d", &m);
    while (m--) {
        int x, y;
        scanf("%s", op);
        if (op[0] == 'Q')  {
            scanf("%d %d", &x, &y);
            printf("%d\n", LCP(x, y));
        } else if (op[0] == 'R') {
            scanf("%d %s", &x, s);
            upd(x, s[0]);
        } else if (op[0] == 'I') {
            scanf("%d %s", &x, s);
            ins(x, s[0]);
        }
    }

    return 0;
}
