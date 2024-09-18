#include <cstdio>
#include <cstring>
using namespace std;
const int N = 100010;
struct Edge {
	int to, nxt;
}edges[N << 1]; int head[N], n, q, nedge;
struct Segment {
	int cnt, l, r;
	Segment operator + (const Segment &rhs) const {
		return (Segment){cnt + rhs.cnt + (r == rhs.l), l, rhs.r};
	}
}seg[N << 2]; int tg[N << 2];
int dfn[N], top[N], tim;
int fa[N], siz[N], hvy[N], dep[N];
inline void swap(int &x, int &y) {x ^= y; y ^= x; x ^= y;}
inline void read(int &x) {
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	x = (c ^ 48); c = getchar();
	while(c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
}
inline void write(int x) {
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline void addedge(int u, int v) {
	edges[++nedge].to = v;
	edges[nedge].nxt = head[u];
	head[u] = nedge;
}
inline void dfs1(int u) {
	siz[u] = 1; hvy[u] = -1;
	for(int i = head[u]; i; i = edges[i].nxt) {
		int v = edges[i].to;
		if(fa[u] == v) continue;
		fa[v] = u; dep[v] = dep[u] + 1;
		dfs1(v); siz[u] += siz[v];
		if(hvy[u] == -1 || siz[v] > siz[hvy[u]]) hvy[u] = v;
	}
}
inline void dfs2(int u, int t) {
	top[u] = t; dfn[u] = ++tim;
	if(hvy[u] == -1) return;
	dfs2(hvy[u], t);
	for(int i = head[u]; i; i = edges[i].nxt) {
		int v = edges[i].to;
		if(fa[u] == v || hvy[u] == v) continue;
		dfs2(v, v);
	}
}
inline void pushup(int p) {
	seg[p] = seg[p << 1] + seg[p << 1 | 1];
}
inline void build(int p, int l, int r) {
	tg[p] = -1;
	if(l == r) {seg[p] = (Segment){0, l, l}; return;}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
inline void pushtag(int p, int l, int r, int t) {
	tg[p] = t; seg[p] = (Segment){r - l, t, t};
}
inline void pushdown(int p, int l, int r) {
	if(tg[p] != -1) {
		int mid = (l + r) >> 1;
		pushtag(p << 1, l, mid, tg[p]);
		pushtag(p << 1 | 1, mid + 1, r, tg[p]);
		tg[p] = -1;
	}
}
inline void modify(int p, int l, int r, int ql, int qr, int t) {
	if(ql <= l && r <= qr) {pushtag(p, l, r, t); return;}
	pushdown(p, l, r); int mid = (l + r) >> 1;
	if(ql <= mid) modify(p << 1, l, mid, ql, qr, t);
	if(qr > mid) modify(p << 1 | 1, mid + 1, r, ql, qr, t);
	pushup(p);
}
inline Segment query(int p, int l, int r, int ql, int qr) {
	if(ql <= l && r <= qr) return seg[p];
	pushdown(p, l, r); int mid = (l + r) >> 1;
	if(qr <= mid) return query(p << 1, l, mid, ql, qr);
	if(ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
	return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
}
inline void doit1(int u, int v, int t) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		modify(1, 1, n, dfn[top[u]], dfn[u], t);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	modify(1, 1, n, dfn[u], dfn[v], t);
}
inline int doit2(int u, int v) {
	bool firu = true, firv = true;
	Segment retu = (Segment){0, 0, 0}, retv = (Segment){0, 0, 0};
	while(top[u] != top[v]) {
		if(dep[top[u]] > dep[top[v]]) {
			if(firu) retu = query(1, 1, n, dfn[top[u]], dfn[u]);
			else retu = query(1, 1, n, dfn[top[u]], dfn[u]) + retu;
			firu = false; u = fa[top[u]];
		} else {
			if(firv) retv = query(1, 1, n, dfn[top[v]], dfn[v]);
			else retv = query(1, 1, n, dfn[top[v]], dfn[v]) + retv;
			firv = false; v = fa[top[v]];
		}
	}
	if(dep[v] <= dep[u]) {
		if(firu) retu = query(1, 1, n, dfn[v], dfn[u]);
		else retu = query(1, 1, n, dfn[v], dfn[u]) + retu;
		firu = false;
	} else {
		if(firv) retv = query(1, 1, n, dfn[u], dfn[v]);
		else retv = query(1, 1, n, dfn[u], dfn[v]) + retv;
		firv = false;
	}
	return retu.cnt + retv.cnt + (!firu && !firv && retu.l == retv.l);
}
int main() {
//	freopen("edge.in", "r", stdin);
//	freopen("edge.out", "w", stdout);
	int T; read(T);
	while(T--) {
		read(n); read(q); nedge = tim = 0;
		for(int u = 1; u <= n; ++u) head[u] = fa[u] = dep[u] = 0;
		for(int i = 1; i < n; ++i) {
			int u, v; read(u); read(v);
			addedge(u, v); addedge(v, u);
		}
		dfs1(1); dfs2(1, 1);
		build(1, 1, n);
		for(int i = 1; i <= q; ++i) {
			int op, u, v; read(op); read(u); read(v);
			if(op == 1) doit1(u, v, n + i);
			else {write(doit2(u, v)); putchar('\n');}
		}
	}
	return 0;
}
