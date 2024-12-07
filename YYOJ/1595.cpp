#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 25e4 + 5;

struct IO {
	static const int BufS=1<<21;
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

int n;
ll a[3];
int f[N][2];
bool g[N][2];
vector<int > es[N];

void dfs(int u, int pre) {
	f[u][1] = 1;
	for (auto &v : es[u]) if (v ^ pre) {
		dfs(v, u);
		if (f[v][0] == f[v][1]) g[v][0] = g[v][1] = 1;
		else g[v][f[v][1] > f[v][0]] = 1; 
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
	}
}

void solve(int u, int pre, int k) {
	a[k]++;
	for (auto &v : es[u]) if (v ^ pre) {
		if (k == 2) {
			if (g[v][1]) solve(v, u, 2);
			else solve(v, u, 0);
		} else if (k == 1) solve(v, u, 0);
		else {
			if (g[v][0] && g[v][1]) solve(v, u, 2);
			else if (g[v][0]) solve(v, u, 0);
			else solve(v, u, 1);
		}
	}
}

int main() {
	io >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		io >> u >> v;
		es[u].push_back(v);
		es[v].push_back(u);
	}
	
	dfs(1, 0); 
	if (f[1][0] == f[1][1]) solve(1, 0, 2);
	else solve(1, 0, f[1][1] > f[1][0]);
	
	printf("%lld", a[2] * (a[2] - 1) / 2 + a[2] * (n - a[2]) + a[0] * (a[0] - 1) / 2 + a[0] * a[1]);
	
	return 0;
} 
