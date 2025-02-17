#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 4;

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

int n, Q, inf, a[N], b[N], rt[N], q[4], ans;
vector<int > pos[N];

namespace Seg {
    struct V {
        int s, lm, rm;
        V(int v = 0) { s = v; lm = rm = max(0, v); }
        V operator + (const V &a) const {
            V r(s + a.s); r.lm = max(lm, s + a.lm); r.rm = max(a.rm, a.s + rm);
            return r;
        }
    };
    int tot;
    struct Node {
        int l, r; V v;
        Node(int v = 0): v(V(v)) { l = r = 0; }
    } o[N * 20];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline int copy(int p) { o[++tot] = o[p]; return tot; }
    inline void up(int p) { o[p].v = o[ls].v + o[rs].v; }
    inline void upd(int &p, int l, int r, const int &x, const int &v) {
        if (l > x || r < x) return;
        p = copy(p);
        if (l == r) return void(o[p] = Node(v));
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline V query(int p, int l, int r, const int &x, const int &y) {
        if (l > y || r < x) return V();
        if (x <= l && r <= y) return o[p].v;
        M; return query(goL, x, y) + query(goR, x, y);
    }
}
using namespace Seg;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1); inf = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, n) a[i] = lower_bound(b + 1, b + inf + 1, a[i]) - b, pos[a[i]].pb(i);
    For (i, 1, n) upd(rt[0], 1, n, i, 1);
    For (i, 1, inf) {
        rt[i] = rt[i - 1];
        for (auto &x : pos[i - 1]) upd(rt[i], 1, n, x, -1);
    }
    io >> Q;
    while (Q--) {
        int x;
        For (i, 0, 3) io >> x, q[i] = (x + ans) % n + 1;
        sort(q, q + 4);
        ans = 0;
        int l = 1, r = inf;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (query(rt[m], 1, n, q[0], q[1] - 1).rm + query(rt[m], 1, n, q[1], q[2]).s + query(rt[m], 1, n, q[2] + 1, q[3]).lm >= 0) ans = m, l = m + 1;
            else r = m - 1;
        }
        printf("%d\n", ans = b[ans]);
    }

    return 0;
}
