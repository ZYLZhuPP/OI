#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 5e5 + 5, M = 1e6 + 5;

template<class C> inline bool chkmin(C &x, const C &y){return x>y? x=y, 1: 0;}

struct IO {
	static const int BufS = 1 << 21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

struct Edge1 {
	int u, v;
	ll tem, t;
	
	bool operator < (const Edge1 &X) const {
		return tem < X.tem;
	}
} ed[M];

struct Edge2 {
	int to;
	ll w;
};
vector<Edge2 > es1[N], es2[N];

ll n, m, S, T, dis[N], fa[N], maT;
bool vis[N];

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i;
}

int find(int u) {
	return u^fa[u]? fa[u] = find(fa[u]): u;
}

void merge(int u, int v) {
	fa[u] = v;
}

void dfs(int u, int pre, ll ma) {
	if (u == T) {
		maT = ma;
		return;
	} 
	
	for (auto &e : es1[u]) if(pre ^ e.to) {
		dfs(e.to, u, max(ma, e.w));
	}
}

void Dijkstra(int rt) {
    memset(vis, 0, sizeof(vis));
    memset(dis, 31, sizeof(dis)); dis[rt] = 0;
	priority_queue<pair<ll, int >, vector<pair<ll, int > >, greater<pair<ll, int > > > q;
	q.push(make_pair(dis[rt], rt));
	
	while (!q.empty()) {
		int u = q.top().second;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto &e : es2[u]) {
			int v = e.to;
			if (chkmin(dis[v], dis[u] + e.w))
		        q.push(make_pair(dis[v], v));
		}
	}
}

int main() {
	io >> n >> m;
	init();
	for (int i = 0; i < m; i++) {
	    io >> ed[i].u >> ed[i].v >> ed[i].tem >> ed[i].t;
	}
	io >> S >> T;
	
	sort(ed, ed + m);
	
	for (int i = 0; i < m; i++) {
		int u = ed[i].u, v = ed[i].v;
		int fu = find(u), fv = find(v);
		
		if (fu ^ fv) {
			merge(fu, fv);
			es1[u].push_back({v, ed[i].tem});
			es1[v].push_back({u, ed[i].tem});
		}
	}
	
	dfs(S, 0, 0);
	
	for (int i = 0; i < m; i++) {
		if (ed[i].tem > maT) break;
		
		int u = ed[i].u, v = ed[i].v;
		ll w = ed[i].tem * ed[i].t;
		es2[u].push_back({v, w});
		es2[v].push_back({u, w});
	} 
	
	Dijkstra(S);
	
	printf("%lld %lld", maT, dis[T]);
	
	return 0;
}

