#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 305;

template<class T> inline bool chkmax(T &x, const T &y) {return x<y? x=y, 1: 0;}

struct Edge {
	int to;
	ll w;
};
vector<Edge > es[N];

ll n, T, val[N], t[N], u, v, w, ans, f[N][N][3];

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

void dfs(int u, int pre) {
	if (t[u] <= T) f[u][t[u]][1] = f[u][t[u]][0] = val[u];
	
	for (auto &e : es[u]) if (pre ^ e.to) {
		int v = e.to, w = e.w;
		dfs(v, u);
		
		for (int i = T; i >= 0; i--) {
			for (int j = i; j >= 0; j--) {
				if (i-j-2*w >= 0) chkmax(f[u][i][2], f[u][j][2] + f[v][i-j-2*w][0]);
				if (i-j-w >= 0) chkmax(f[u][i][2], f[u][j][1] + f[v][i-j-w][1]);
				if (i-j-2*w >= 0) chkmax(f[u][i][2], f[u][j][0] + f[v][i-j-2*w][2]);
				if (i-j-2*w >= 0) chkmax(f[u][i][1], f[u][j][1] + f[v][i-j-2*w][0]);
				if (i-j-w >= 0) chkmax(f[u][i][1], f[u][j][0] + f[v][i-j-w][1]);
				if (i-j-2*w >= 0) chkmax(f[u][i][0], f[u][j][0] + f[v][i-j-2*w][0]);
			}
		}
	}
	
	for (int i = 0; i <= T; i++) chkmax(ans, f[u][i][0]), chkmax(ans, f[u][i][1]), chkmax(ans, f[u][i][2]);
}

int main() {
	memset(f, 224, sizeof(f));
	
	io >> n >> T;
	for (int i = 1; i <= n; i++) io >> val[i];
	for (int i = 1; i <= n; i++) io >> t[i];
	for (int i = 1; i < n; i++) {
	    io >> u >> v >> w;
		es[u].push_back({v, w});
		es[v].push_back({u, w});
	}
	
	dfs(1, 0);
	
	printf("%lld", ans);
	
	return 0; 
}

