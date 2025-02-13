#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

struct Edge {
	int to;
	ll w;
	
	bool operator < (const Edge &X) const {
		return w > X.w;
	}
};
vector<Edge > es[N];

int n, m, S, T, X, Y, u, v, w;
bool vis[N];
ll dis[3][N], ans;

template<class C> inline bool chkmin(C &x, const C &y) {return x>y? x=y, 1: 0;}

void dij(int rt, int k) {
	memset(vis, 0, sizeof(vis));
	priority_queue<Edge > q;
	q.push({rt, dis[k][rt] = 0});
	while (!q.empty()) {
		int u = q.top().to; q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto &e : es[u]) if (!vis[e.to]) {
			int v = e.to;
			ll w = e.w;
			if (chkmin(dis[k][v], dis[k][u] + w)) q.push({v, dis[k][v]});
		}
	}
}

void dfs(int u, ll mx, ll my) {
	vis[u] = 1;
	chkmin(ans, mx + my);
	for (auto &e : es[u]) if (!vis[e.to]) {
		int v = e.to;
		ll w = e.w;
		if (dis[0][v] + w == dis[0][u]) dfs(v, min(mx, dis[1][v]), min(my, dis[2][v]));
	}
} 

int main() {
	io >> n >> m;
	io >> S >> T;
	io >> X >> Y;
	for (int i = 1; i <= m; ++i) {
		io >> u >> v >> w;
		es[u].push_back({v, w});
		es[v].push_back({u, w});
	}
	
	memset(dis, 31, sizeof(dis));
	dij(S, 0); dij(X, 1); dij(Y, 2);
	
	ans = dis[1][Y];
	memset(vis, 0, sizeof(vis));
	dfs(T, dis[1][T], dis[2][T]);
	
	printf("%lld", ans);
	
	return 0;
}

