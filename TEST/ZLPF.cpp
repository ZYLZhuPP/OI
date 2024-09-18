#include<bits/stdc++.h>
using namespace std;

#define cl(a, b) memset(a, b, sizeof(a))

template<class C> inline void clear(C &a) { C().swap(a); }

const int N = 1e5 + 5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

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
		
		Node operator + (const Node &x) {
			return !use? x: (!x.use? (*this):
				Node(1, lco, x.rco, sum + x.sum + (~rco && rco == x.lco)));
		}
		
		void update(P, int tag) { lco = rco = this->tag = tag; sum = r - l; }
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
	
	void build(P) {
		if (l == r) return (void)(tr[p] = Pt(1));
		Mid;
		build(ls); build(rs);
		pushup(me);
	}
	
	void rebuild(int n) {
		tr.resize((n << 2) + 1, Pt(0));
		build(1, 1, n);
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

int n, m, T, color;
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
	return res1.sum + res2.sum + (~res1.lco && res1.lco == res2.lco);
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

void init() {
	color = tim = 0;
	tr.rebuild(n);
	for (int i = 1; i <= n; i++) clear(es[i]);
	cl(son, 0); 
}

int main() {
	io>>T;
	while (T--) {
		io >> n >> m;
		init();
		for (int i = 1; i < n; i++) {
			int u, v;
			io >> u >> v;
			es[u].emplace_back((Edge){v});
			es[v].emplace_back((Edge){u});
		}
		dfs1(1, 0); dfs2(1, 1);
		while (m--) {
			int opt, u, v;
			io >> opt >> u >> v;
			if (opt == 1) chain_modify(u, v, ++color);
			if (opt == 2) printf("%d\n", chain_query(u,v));
		}
	}
	return 0;
}
