#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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
	inline bool operator ~ () { return ~c; }
} io;

int dfn[N], dfn_[N], a[N], n, m, tim = 1;
vector<int > es[N];

namespace Splay {
	int ch[N][2], fa[N], val[N], w[N], sz[N], tot, rt;
	ll s[N], tag[N];
#define ls ch[u][0]
#define rs ch[u][1]
#define fu fa[u]
	bool is(int u) { return ch[fu][1] == u; }
	void up(int u) { s[u] = s[ls] + s[rs] + val[u], sz[u] = sz[ls] + sz[rs] + w[u]; }
	void mark(int u, const ll &d) {	if (u) s[u] += sz[u] * d, val[u] += w[u] * d, tag[u] += d; }
	void down(int u) { if (tag[u]) mark(ls, tag[u]), mark(rs, tag[u]), tag[u] = 0; }
	void updown(int u) { if (fu) updown(fu); down(u); }
	void add(int f, int u, int k) { ch[fu = f][k] = u; }
	void rot(int u) {
	    int p = fu, k = is(u);
	    add(p, ch[u][!k], k);
	    add(fa[p], u, is(p));
	    add(u, p, !k);
	    up(p), up(u);
	}
	void splay(int u, int to) {
	    to = fa[to];
	    updown(u);
	    for (; fu ^ to; rot(u)) if (fa[fu] ^ to) rot(is(u)^is(fu)? u: fu);
	    if (!to) rt = u;
	}
	int pre(int u) {
	    splay(u, rt);
	    u = ls;
	    while (rs) u = rs;
	    return u;
	}
	int suf(int u) {
	    splay(u, rt);
	    u = rs;
	    while (ls) u = ls;
	    return u;
	}
	void upd(int l, int r, const ll &d) {
	    l = pre(l), r = suf(r);
	    splay(r, rt), splay(l, ch[r][0]);
	    int u = ch[l][1];
	    tag[u] += d, s[u] += d * sz[u], val[u] += d * w[u];
	    up(l), up(r);
	}
	void move(int l, int r, int f) {
	    l = pre(l), r = suf(r);
	    splay(r, rt), splay(l, ch[r][0]);
	    int u = ch[l][1];
	    fa[u] = ch[l][1] = 0;
	    up(l), up(r);
	    
	    int v = suf(f);
	    splay(v, ch[f][1]);
	    add(v, u, 0);
	    up(v), up(f);
	}
	void build(int &u, int l, int r) {
	    if (l > r) return void(u = 0);
	    u = (l + r) >> 1;
	    build(ls, l, u - 1), build(rs, u + 1, r);
	    fa[ls] = fa[rs] = u;
	    up(u);
	}
}
using namespace Splay;

void dfs(int u) {
    val[dfn[u] = ++tim] = a[u];
    w[tim] = 1;
    for (auto &v : es[u]) dfs(v);
    val[dfn_[u] = ++tim] = -a[u];
    w[tim] = -1;
}

int main() {
    int u, v, d;
    char op[5];
    io >> n;
    For (i, 2, n) io >> u, es[u].pb(i);
    For (i, 1, n) io >> a[i];
    dfs(1);
    build(rt, 1, ++tim);
    io >> m;
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'Q') {
            io >> u; u = pre(dfn_[u]);
	    	splay(u, rt);
	    	printf("%lld\n", s[ls] + val[u]);
        } else if (op[0] == 'C') {
            io >> u >> v;
            move(dfn[u], dfn_[u], dfn[v]);
        } else if (op[0] == 'F') {
            io >> u >> d;
            upd(dfn[u], dfn_[u], d);
        }
    }

    return 0;
}
