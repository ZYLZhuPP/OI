#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y) { return x<=y? x=y, 1: 0; }
template<class C> inline bool chkmin(C &x, const C &y) { return x>=y? x=y, 1: 0; }

typedef long long ll;

const int N = 1e5 + 5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) f|=-!(c^45);
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct Edge {
	int to;
	ll w;
};
vector<Edge > es[N];

ll n, m, ans, Ans, f[N], h1[N], h2[N], g1[N], g2[N], sum[N];
vector<int > cir;
bool incir[N];

int fa[N], dep[N];
void find_circle(int u, int pre) {
	dep[u] = dep[fa[u] = pre] + 1;
	for (auto &e: es[u]) if(e.to ^ pre) {
		int v = e.to;
		if (!dep[v])
			find_circle(v, u);
		else if(dep[v] < dep[u]) {
			for (int i = u; dep[i] >= dep[v]; i = fa[i])
				cir.emplace_back(i), incir[i] = 1;
		}
	}
}

void dfs_tree(int u, int pre) {
	for (auto &e: es[u]) if(e.to ^ pre && !incir[e.to]) {
		int v = e.to;
		dfs_tree(v, u); f[v] += e.w;
		chkmax(ans, f[u] + f[v]); chkmax(f[u], f[v]);
	}
}

void double_circle() {
	for (int i = 0; i < m; i++)
		cir.emplace_back(cir[i]);
}

Edge get_e(int u, int v) {
	for (auto &e: es[u])
		if (e.to == v)
			return e;
}

void init_sum() {
	for (int i = 1; i < m; i++) 
		sum[i] = sum[i - 1] + get_e(cir[i], cir[i - 1]).w; 
}

int main() {
	io >> n;
	for (int i = 1; i <= n; i++) {
		int u, v; ll w;
		io >> u >> v >> w;
		es[u].emplace_back((Edge){v, w});
		es[v].emplace_back((Edge){u, w});
	}
	
	find_circle(1, 0);
	m = cir.size();
	for (auto &u: cir) 
		dfs_tree(u, -1);
	
	init_sum(); ll D = get_e(cir[0], cir[m - 1]).w;
	ll mx = f[cir[0]]; h1[0] = f[cir[0]];
	for(int i = 1; i < m; i++) {
		h1[i] = max(h1[i - 1], f[cir[i]] + sum[i]);
		g1[i] = max(g1[i - 1], f[cir[i]] + sum[i] + mx);
		chkmax(mx, f[cir[i]] - sum[i]);
	}
	mx = f[cir[m - 1]] + sum[m - 1]; h2[m - 1] = f[cir[m - 1]];
	for(int i = m - 2; i >= 0;i--){
		h2[i] = max(h2[i + 1], f[cir[i]] + sum[m - 1] - sum[i]);
		g2[i] = max(g2[i + 1], f[cir[i]] - sum[i] + mx);
		chkmax(mx, f[cir[i]] + sum[i]);
	}

	Ans = g2[0];
	for (int i = 0; i < m - 1; i++)
		chkmin(Ans, max(g1[i], max(g2[i+1], h1[i] + h2[i+1] + D)));
	chkmax(Ans, ans);
	printf("%.1f", Ans / 2.0);
	return 0;
}
