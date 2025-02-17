#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5, inf = 1e4;

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

namespace Seg {
    int tot;
    struct Node {
        int l, r, sz;
        Node(int sz = 0): sz(sz) { l = r = 0; }
    } o[N << 4];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline int copy(int p) { o[++tot] = o[p]; return tot; }
    inline void up(int p) { o[p].sz = o[ls].sz + o[rs].sz; }
    inline void upd(int &p, int l, int r, const int &x) {
        if (l > x || r < x) return;
        p = copy(p);
        if (l == r) return void(o[p].sz++);
        M; upd(goL, x); upd(goR, x); up(p);
    }
    inline int query(int p, int l, int r, int q, const int &k) {
        if (o[q].sz - o[p].sz <= k) return 0;
        if (l == r) return l;
        M; return query(goL, o[q].l, k) + query(goR, o[q].r, k);
    }
}
using namespace Seg;

int n, m, rt[N];

int main() {
    int x, l, r;
    io >> n >> x;
    For (i, 1, n) io >> x, upd(rt[i] = rt[i - 1], 1, inf, x);
    io >> m;
    while (m--) {
        io >> l >> r;
        x = query(rt[l - 1], 1, inf, rt[r], (r - l + 1) >> 1);
        if (x) printf("yes %d\n", x);
        else puts("no");
    }

    return 0;
}
