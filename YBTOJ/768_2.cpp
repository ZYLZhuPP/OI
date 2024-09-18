#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

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

class SMT{
#define lc (p << 1)
#define rc (p <<1 | 1)
#define me p, l, r
#define ls lc, l, mid
#define rs rc, mid + 1, r
#define Mid int mid = ((l + r) >> 1)
#define P int p, int l, int r
public:
	typedef struct Node {
		bool use;
		int lco, rco, sum, tag;
		
		Node(bool use, int lco = -1, int rco = -1, int sum = 0, int tag = -1): use(use), lco(lco), rco(rco), sum(sum), tag(tag) {}
		
		Node operator + (const Node &x) const {
			return !use? x: (!x.use? (*this):
				Node(1, lco, x.rco, sum + x.sum - (rco == x.lco)));
		}
		
		void update(P, int tag) { use = 1; lco = rco = this->tag = tag; sum = 1; }
	}Pt;

private:
	vector<Node > tr;
	
	void pushup(P) { tr[p] = tr[lc] + tr[rc]; }
	
	void pushdown(P) {
		Mid; int &tag = tr[p].tag;
		if (~tag) {
			tr[lc].update(ls, tag);
			tr[rc].update(rs, tag);
			tag=-1;
		}
	}
	
public:
	const int maxn;
	
	SMT(int maxn): maxn(maxn) {
		tr.reserve((maxn << 2) + 1);
	}

	void range_modify(P, int L, int R, int co) {
		if (r < L || R < l) return;
   		if (L <= l && r <= R) return tr[p].update(me, co);
    	Mid;
    	pushdown(me);
    	range_modify(ls, L, R, co); range_modify(rs, L, R, co);
    	pushup(me);
	}
	
	void pt_modify(P, int goal, int co) {
		range_modify(me, goal, goal, co);
	}
	
	Node range_query(P, int L, int R) {
		if (r < L || R < l) return Node(0);
    	if (L <= l && r <= R) return tr[p];
    	Mid; Node res(0);
    	pushdown(me);
    	res = range_query(ls, L, R) + range_query(rs, L, R);
    	return res;
	}
	
	Node pt_query(P, int goal) {
		return range_query(me, goal, goal);
	}
}tr(N);

struct Edge {
	int to;
};
vector<Edge > es[N];

int n, m, w[N];
int son[N], siz[N], top[N], dfn[N], dfn_[N], dep[N], tim, fa[N];
int id[N];

#define fo(u) for(auto &e: es[u])
#define V int v = e.to

void dfs1(int u, int pre) {
	fa[u] = pre;
	siz[u] = 1;
	dep[u] = dep[pre] + 1;
	fo(u) {
		V; if (v == pre) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
} 

void dfs2(int u, int peak) {
	top[u] = peak;
	dfn[u] = ++tim;
	id[tim] = u;
	if (!son[u]) return;
	dfs2(son[u], peak);
	fo(u) {
		V; if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
	dfn_[u] = tim;
}

void chain_modify(int u, int v, int co) {
	int fu = top[u], fv = top[v];
    while (fu ^ fv) {
        if (dep[fu] < dep[fv]) swap(u, v), swap(fu, fv);
        tr.range_modify(1, 1, n, dfn[fu], dfn[u], co);
        u = fa[fu], fu = top[u];
    }
    if (dep[u] > dep[v]) swap(u, v);
    tr.range_modify(1, 1, n, dfn[u], dfn[v], co);
}

int chain_query(int u, int v) {
	int fu = top[u], fv = top[v];
	SMT::Node res1(0), res2(0);
	while (fu ^ fv) {
		if (dep[fu] < dep[fv]) swap(u, v), swap(fu, fv), swap(res1, res2);
        res1 = tr.range_query(1, 1, n, dfn[fu], dfn[u]) + res1;
        u = fa[fu], fu = top[u];
	}
	if (dep[u] > dep[v]) swap(u, v), swap(res1, res2);
	res2 = tr.range_query(1, 1, n, dfn[u], dfn[v]) + res2;
	return res1.sum + res2.sum - (res1.lco == res2.lco);
}

void tree_modify(int rt, int co) {
	tr.range_modify(1, 1, n, dfn[rt], dfn_[rt], co);
}

int tree_query(int rt) {
	return tr.range_query(1, 1, n, dfn[rt], dfn_[rt]).sum;
}

void pt_modify(int p, int co) {
	tr.pt_modify(1, 1, n, p, co);
}

int pt_query(int p) {
	return tr.pt_query(1, 1, n, p).sum;
}

int main() {
    io >> n >> m;
    for (int i = 1; i <= n; ++i) io >> w[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        io >> u >> v;
        es[u].emplace_back((Edge){v});
        es[v].emplace_back((Edge){u});
    }
    dfs1(1, 0); dfs2(1, 1);
    for (int i = 1; i <= n; ++i) tr.pt_modify(1, 1, n, dfn[i], w[i]);
    while (m--) {
        char op;
        cin >> op;
        int u, v, c;
        io >> u >> v;
        if (op == 'C') io >> c, chain_modify(u, v, c);
        else printf("%d\n", chain_query(u,v));
    }
	return 0;
}
