#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5, inf = 1e9;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, Q, q[N], ans[N];
vector<int > op[N];

namespace Seg {
    struct Node {
        int s, t;
        Node(int s = 0): s(s) { t = 0; }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define me p, l, r
#define goL ls, l, m
#define goR rs, m + 1, r
#define P int p, int l, int r
    inline void up(int p) { o[p].s = o[ls].s + o[rs].s; }
    inline void mark(P, const int &d) { if (p) o[p].s += d * (r - l + 1), o[p].t += d; }
    inline void down(P) { M; if (o[p].t) mark(goL, o[p].t), mark(goR, o[p].t), o[p].t = 0; }
    inline void upd(P, const int &x, const int &y, const int &v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(me, v);
        down(me); M; upd(goL, x, y, v); upd(goR, x, y, v); up(p);
    }
    inline int query(int p, int l, int r, const int &x, const int &y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p].s;
        down(me); M; return query(goL, x, y) + query(goR, x, y);
    }
}

namespace Heavy {
    int fa[N], top[N], son[N], siz[N], dep[N], dfn[N], dfn_[N], tim;
    vector<int > es[N];
    inline void dfs0(int u, int pre) {
        fa[u] = pre; dep[u] = dep[pre] + 1; siz[u] = 1;
        for (auto &v : es[u]) if (v ^ pre) {
            dfs0(v, u); siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
    inline void dfs1(int u, int t) {
        dfn[u] = ++tim; top[u] = t;
        if (son[u]) dfs1(son[u], t);
        for (auto &v : es[u]) if (!top[v]) dfs1(v, v);
        dfn_[u] = tim;
    }
    void init(int rt = 1) {
        dfs0(rt, 0); dfs1(rt, rt);
    }
    void upd(int u) {
        while (u) {
            Seg::upd(1, 1, n, dfn[top[u]], dfn[u], 1);
            u = fa[top[u]];
        }
    }
    int query(int u) {
        int res = 0;
        while (u) {
            res += Seg::query(1, 1, n, dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        return res;
    }
}
using namespace Heavy;

int main() {
    io >> n >> Q;
    For (i, 2, n) io >> fa[i], es[++fa[i]].pb(i);
    init();
    For (i, 1, Q) {
        int l, r;
        io >> l >> r >> q[i]; l++; r++; q[i]++;
        op[r].pb(i); op[l - 1].pb(-i);
    }
    For (i, 1, n) {
        upd(i);
        for (auto &x : op[i])
            if (x > 0) ans[x] += query(q[x]);
            else x = -x, ans[x] -= query(q[x]);
    }
    For (i, 1, Q) printf("%d\n", ans[i] % 201314);

    return 0;
}
