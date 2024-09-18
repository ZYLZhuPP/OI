#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e4 + 5, K = 18, K_2 = 1<<K;

template<class C> inline bool chkmin(C &x, const C &y){return x>y? x=y, 1: 0;}

struct Node {
	ll u, sta;
};

struct Edge {
	ll to, w;
};
vector<Edge > es[N];

ll n, m, k, t, dis[N], dis_[K][K_2], cnt[K_2], ma, ans, g[K][K], u, v, w, pos[K];
bool inq[N], inq_[K][K_2];

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

void SPFA(ll rt) {
	memset(dis, 31, sizeof(dis)); dis[rt] = 0;
	memset(inq, 0, sizeof(inq)); inq[rt] = 1;
	queue<ll > q; q.push(rt);
	while (!q.empty()) {
		ll u = q.front(); q.pop(); inq[u] = 0;
		ll siz = es[u].size();
		for (ll i = 0; i < siz; i++) {
			ll v = es[u][i].to;
			if (chkmin(dis[v], dis[u] + es[u][i].w)) 
				if (!inq[v]) q.push(v), inq[v] = 1;
		}
	}
}

void SPFA_() {
	memset(dis_, 31, sizeof(dis_)); dis_[0][1] = 0;
	memset(inq_, 0, sizeof(inq_)); inq_[0][1] = 1;
	queue<Node > q; q.push({0, 1});
	cnt[1] = 0;
	while (!q.empty()) {
		ll u = q.front().u, sta = q.front().sta; q.pop(); inq_[u][sta] = 0;
		for (ll v = 0; v <= k; v++) {
			ll sta_ = sta | (1<<v);
			if (sta_ > sta) cnt[sta_] = cnt[sta] + (v != k);
			if (chkmin(dis_[v][sta_], dis_[u][sta] + g[u][v])) 
				if (!inq_[v][sta_]) q.push({v, sta_}), inq_[v][sta_] = 1;
		}
	}
}

int main() {
    io >> n >> m >> k >> t;
	for (ll i = 1; i <= m; i++) {
        io >> u >> v >> w;
		es[u].push_back({v, w});
		es[v].push_back({u, w});
	}
	for (ll i = 1; i <= k; i++) io >> pos[i]; pos[++k] = n; pos[0] = 1;
	
	memset(g, 31, sizeof(g));
	for (ll i = 0; i <= k; i++) {
		SPFA(pos[i]);
		for (ll j = 0; j <= k; j++) g[i][j] = dis[pos[j]];
	}
	if (2*g[0][k] > t) {
		puts("-1");
		return 0;
	}
	
	SPFA_();
	
	ma = -1;
	for (ll sta = 1; sta < 1 << k; sta++) {
		ll s = sta + (1<<k);
		for (ll u = 0; u <= k; u++) {
			if (dis_[u][s] + g[0][u] <= t) {
				if (cnt[s] > ma) {
					ma = cnt[s]; ans = dis_[u][s] + g[0][u];
				}else if (cnt[s] == ma) chkmin(ans, dis_[u][s] + g[0][u]);
			}
		}
	}
	
	printf("%lld %lld", ma, ans);
	return 0;
} 

