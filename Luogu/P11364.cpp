#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
template<class C > inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

struct BIT {
    int o1[N], o2[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int v) {
        for (int l = x - 1; l; l -= lowbit(l)) cmax(o1[l], v);
        for (int r = x; r < N; r += lowbit(r)) cmax(o2[r], v);
    }
    inline int query(int l, int r) {
        if (l > r) return 0;
        int res = 0;
        if (--l) for (; l + lowbit(l) <= r; l += lowbit(l)) cmax(res, o1[l]);
        for (; l ^ r; r -= lowbit(r)) cmax(res, o2[r]);
        return res;
    }
} tr[4];

int n, q, id[N], fa[N], dep[N], ls[N], rs[N], a[N], ans[N];
vector<int > es[N];
vector<array<int, 3 > > op1[N], q1[N];
vector<array<int, 2 > > op2[N], q2[N], qs[N];

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

inline void dfs0(int u, int pre) {
    dep[u] = dep[pre] + 1; tr[0].upd(u, dep[u]);
    for (auto &[v, id] : qs[u]) if (fa[v]) a[id] = dep[find(v)];
    fa[u] = u;
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u), fa[v] = u;
}

inline bool cmp(const int &x, const int &y) { return a[x] > a[y]; }

int main() {
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u), qs[i].pb({i + 1, i}), qs[i + 1].pb({i, i});
    dfs0(1, 0);
    io >> q;
    int l, r, k;
    For (i, 1, q) {
        io >> l >> r >> k;
        if (k == 1) ans[i] = tr[0].query(l, r);
        else q1[k - 1].pb({l, r, i}), q2[l].pb({r, i});
    }
    For (i, 1, n - 1) fa[i] = 0, ls[i] = i, rs[i] = i, id[i] = i;
    ls[1] = 1; rs[n - 1] = n - 1;
    sort(id + 1, id + n, cmp);
    For (i, 1, n - 1) {
        int x = id[i]; fa[x] = x;
        if (ls[x] > 1 && fa[ls[x] - 1]) {
            ls[x] = find(ls[x] - 1);
            fa[ls[x]] = x;
            ls[x] = ls[ls[x]];
        }
        if (rs[x] < n - 1 && fa[rs[x] + 1]) {
            rs[x] = find(rs[x] + 1);
            fa[rs[x]] = x;
            rs[x] = rs[rs[x]];
        }
        int len = rs[x] - ls[x] + 1;
        op1[len].pb({ls[x], rs[x], a[x]});
        op2[ls[x]].pb({rs[x], a[x]});
    }

    rFor (i, n, 1) {
        for (auto &[l, r, x] : op1[i]) tr[1].upd(l, x), tr[2].upd(r, x);
        for (auto &[l, r, id] : q1[i]) cmax(ans[id], tr[1].query(l, r - i)), cmax(ans[id], tr[2].query(l + i - 1, r - 1));
    }

    For (i, 1, n) {
        for (auto &[r, x] : op2[i]) tr[3].upd(r, x);
        for (auto &[r, id] : q2[i]) cmax(ans[id], tr[3].query(r - 1, n));
    }

    For (i, 1, q) printf("%d\n", ans[i]);

    return 0;
}
