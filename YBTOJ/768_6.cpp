#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e4 + 5, M = 55, X = 1 << 16, Y = INT_MAX;
int A, B, Q;
inline int Getint() { A=((A^B)+B/X+B*X)&Y; B=((A^B)+A/X+A*X)&Y; return (A^B)%Q; }

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

int n, m, T;

struct V {
    int o[M];
    V() { memset(o, 0, sizeof o); }
    V operator + (const V &a) const {
        V r;
        For (i, 0, m) For (j, 0, m - i) r.o[i + j] = max(r.o[i + j], o[i] + a.o[j]);
        return r;
    }
    V operator * (const V &a) const {
        V r = a;
        For (i, 0, m) r.o[i] = max(r.o[i], o[i]);
        return r;
    }
};
inline V gen() { V v; For (i, 1, m) v.o[i] = Getint(); sort(v.o, v.o + m + 1); return v; }

namespace Seg1 {
    typedef V Node;
    Node o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] + o[rs]; }
    inline void upd(int p, int l, int r, const int &x, const V &v) {
        if (l > x || r < x) return;
        if (l == r) return void(o[p] = v);
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline Node query(int p, int l, int r, const int &x, const int &y) {
        if (l > y || r < x) return Node();
        if (x <= l && r <= y) return o[p];
        M; return query(goL, x, y) + query(goR, x, y);
    }
}

namespace Seg2 {
    typedef V Node;
    Node o[N << 2];
    inline void up(int p) { o[p] = o[ls] * o[rs]; }
    inline void upd(int p, int l, int r, const int &x, const V &v) {
        if (l > x || r < x) return;
        if (l == r) return void(o[p] = v);
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline Node query(int p, int l, int r, const int &x, const int &y) {
        if (l > y || r < x) return Node();
        if (x <= l && r <= y) return o[p];
        M; return query(goL, x, y) * query(goR, x, y);
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
        For (i, 1, n) {
            V v = gen();
            Seg1::upd(1, 1, n, dfn[i], v);
            Seg2::upd(1, 1, n, dfn[i], v);
        }
    }
    void upd(int u) {
        V v = gen();
        Seg1::upd(1, 1, n, dfn[u], v);
        Seg2::upd(1, 1, n, dfn[u], v);
    }
    V query(int u, int v) {
        V res;
        while (top[u] ^ top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            res = res * Seg2::query(1, 1, n, dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) swap(u, v);
        res = res * Seg2::query(1, 1, n, dfn[v], dfn[u]);
        return res;
    }
}
using namespace Heavy;

int main() {
    io >> n >> m >> A >> B >> Q;
    For (i, 2, n) io >> fa[i], es[fa[i]].pb(i);
    init();
    io >> T;
    while (T--) {
        int op, x, y;
        io >> op;
        if (op == 0) {
            io >> x;
            upd(x);
        } else if (op == 1) {
            io >> x >> y;
            V v = Seg1::query(1, 1, n, dfn[x], dfn_[x]);
            if (x ^ y) v = v + query(fa[x], y);
            printf("%d\n", v.o[m]);
        }
    }

    return 0;
}
