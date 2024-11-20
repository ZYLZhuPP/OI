#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

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

int n, O, a[N], p[N], rt[N];
ll ans[N];
set<int > pos;
multiset<ll, greater<ll > > se;

namespace Seg {
    struct Node {
        int l, r, s;
        Node() { l = r = s = 0; }
    } o[N << 5];
    int tot, rub[N << 5], top;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void node(int &p) { p = top? rub[top--]: ++tot; }
    inline void del(int &p) { rub[++top] = p; o[p] = Node(); p = 0; }
    inline void up(int &p) { if (!o[p].s) del(p); }
    inline void upd(int &p, int l, int r, int x, int d) {
        if (!p) node(p);
        o[p].s += d;
        if (l == r) return up(p);
        M; x<=m? upd(goL, x, d): upd(goR, x, d); up(p);
    }
    inline int query0(int p, int l, int r, int x) {
        if (!p || l >= x) return 0;
        if (r < x) return o[p].s;
        M; return query0(goL, x) + query0(goR, x);
    }
    inline int query1(int p, int l, int r, int x) {
        if (!p || r <= x) return 0;
        if (l > x) return o[p].s;
        M; return query1(goL, x) + query1(goR, x);
    }
}
using namespace Seg;

inline void solve(int l, int x, int r) {
    ll res = ans[l]; se.erase(se.find(res));
    M; pos.insert(x);
    if (x <= m) {
        swap(rt[l], rt[x]);
        For (i, l + 1, x) upd(rt[x], 1, n, a[i], -1), res -= query0(rt[x], 1, n, a[i]);
        ans[x] = res; se.insert(res);
        res = 0;
        For (i, l + 1, x - 1) res += query1(rt[l], 1, n, a[i]), upd(rt[l], 1, n, a[i], 1);
        ans[l] = res; se.insert(res);
    } else {
        rFor (i, r - 1, x) upd(rt[l], 1, n, a[i], -1), res -= query1(rt[l], 1, n, a[i]);
        ans[l] = res; se.insert(res);
        res = 0;
        For (i, x + 1, r - 1) res += query1(rt[x], 1, n, a[i]), upd(rt[x], 1, n, a[i], 1);
        ans[x] = res; se.insert(res);
    }
}

int main() {
    io >> n >> O;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) io >> p[i];
    pos.insert(0); pos.insert(n + 1);
    For (i, 1, n) ans[0] += query1(rt[0], 1, n, a[i]), upd(rt[0], 1, n, a[i], 1);
    se.insert(ans[0]);
    For (i, 1, n) {
        ll Ans = *se.begin();
        printf("%lld ", Ans);
        p[i] = (p[i] + O * Ans) % n + 1;
        auto b = pos.upper_bound(p[i]), a = prev(b);
        solve(*a, p[i], *b);
    }

    return 0;
}
