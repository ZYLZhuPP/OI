#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 1e9 + 7, inf = 1e9;

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
	inline bool operator ~ () {return ~c;}
} io;

int n, T, tim, x, C, q, a, c, l, ans;
int dep[N], dfn[N], dfn_[N];
vector<int > es[N];

namespace KDT {
    int D, rt;
#define F(i) For(i, 0, 1)
    struct P {
        int o[2], v;
        P(int x = 0, int y = 0, int v = 1): v(v) { o[0] = x; o[1] = y; }
        int operator [] (const int &i) const { return o[i]; }
        bool operator < (const P &a) const { return o[D] < a.o[D]; }
    };
    struct Node {
        int l, r, t, x[2][2];
        P v;
        Node() { l = r = t = 0; F(i) x[i][0] = inf, x[i][1] = -inf; }
        Node(const P &p): v(p) { l = r = t = 0; F(i) F(j) x[i][j] = p[i]; }
        Node(const int &a, const int &b, const int &c, const int &d) { x[0][0] = a; x[0][1] = b; x[1][0] = c; x[1][1] = d; }
        bool out(const Node &a) const { F(i) if (x[i][0] > a.x[i][1] || x[i][1] < a.x[i][0]) return 1; return 0; }
        bool in(const Node &a) const { F(i) if (x[i][0] < a.x[i][0] || x[i][1] > a.x[i][1]) return 0; return 1; }
    } o[N];
#define ls o[u].l
#define rs o[u].r
    inline void up(int u) { F(i) o[u].x[i][0] = min(o[u].v[i], min(o[ls].x[i][0], o[rs].x[i][0])), o[u].x[i][1] = max(o[u].v[i], max(o[ls].x[i][1], o[rs].x[i][1])); }
    inline void mark(int u, const int &c) { o[u].v.v = o[u].t = c; }
    inline void down(int u) { if (o[u].t) mark(ls, o[u].t), mark(rs, o[u].t), o[u].t = 0; }
    int build(int l, int r, int d = 0) {
        if (l > r) return 0;
        int m = (l + r) >> 1, u = m;
        D = d; nth_element(o + l, o + m, o + r + 1, [&](const Node &a, const Node &b) { return a.v < b.v; } );
        ls = build(l, m - 1, d ^ 1); rs = build(m + 1, r, d ^ 1); up(u);
        return u;
    }
    void upd(int u, const Node &p, const int &c) {
        if (!u || o[u].out(p)) return;
        if (o[u].in(p)) return mark(u, c);
        if (Node(o[u].v).in(p)) o[u].v.v = c;
        down(u); upd(ls, p, c); upd(rs, p, c);
    }
    int query(int u, const P &p) {
        if (!u || Node(p).out(o[u])) return 0;
        if (p[0] == o[u].v[0] && p[1] == o[u].v[1]) return o[u].v.v;
        down(u); return query(ls, p) + query(rs, p);
    }
}
using namespace KDT;

void dfs(int u, int pre) {
    dfn[u] = ++tim; dep[u] = dep[pre] + 1;
    for (auto &v : es[u]) dfs(v, u);
    dfn_[u] = tim;
}

int main() {
    io >> T;
    while (T--) {
        ans = tim = 0;
        io >> n >> C >> q;
        For (i, 1, n) es[i].resize(0);
        For (i, 2, n) io >> x, es[x].pb(i);
        dfs(1, 0);
        For (i, 1, n) o[i] = Node(P(dfn[i], dep[i]));
        rt = build(1, n);
        For (o, 1, q) {
            io >> a >> l >> c;
            if (c == 0) ans = (ans + 1ll * o * query(rt, P(dfn[a], dep[a]))) % Mo;
            else upd(rt, Node(dfn[a], dfn_[a], dep[a], dep[a] + l), c);
        }
        printf("%d\n", ans);
    }

    return 0;
}
