#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int R, C, n;
ll ans;
vector<int > pt[N];

namespace Treap {
    struct Node { int l, r, v, h, sz; ll s; } o[N];
    int rt, x, y, tot;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, u, o[v].l
#define goR rs, o[u].r, v
    inline int up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; o[p].s = o[ls].s + o[rs].s + 1ll * o[p].h * (o[ls].sz + 1) * (o[rs].sz + 1); return p; }
    inline void build(int &p, int l, int r) {
        if (l > r) return void(p = 0);
        M; p = ++tot; o[p].v = m; o[p].sz = 1;
        build(ls, l, m - 1); build(rs, m + 1, r); up(p);
    }
    inline void split(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        if (o[p].v <= k) u = p, split(goR, k), up(u);
        else v = p, split(goL, k), up(v);
    }
    inline int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].h > o[v].h) return o[u].r = merge(o[u].r, v), up(u);
        else return o[v].l = merge(u, o[v].l), up(v);
    }
    inline void ins(int v, int h) {
        split(rt, rt, x, v - 1); split(x, x, y, v);
        o[x].h = h; up(x);
        rt = merge(rt, merge(x, y));
    }
}
using namespace Treap;

int main() {
    io >> R >> C >> n;
    For (i, 1, n) io >> x >> y, pt[x].pb(y);
    build(rt, 1, C);
    For (i, 1, R) {
        for (auto j : pt[i]) ins(j, i);
        ans += o[rt].s;
    }
    printf("%lld", ans);

    return 0;
}
