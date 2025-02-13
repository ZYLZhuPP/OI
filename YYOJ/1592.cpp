#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

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
	inline bool operator ~ () {return ~c;}
} io;

struct Node {
	ll a, b;
	bool operator < (const Node &X) const {
		if (b >= 0) return a > X.a;
		return b - a > X.b - X.a;
	}
};
vector<Node > H[N], L[N];

struct Edge {
	int to;
	ll w;
};
vector<Edge > es[N];

int n, u, v;
ll w, a[N], sum[N], mi[N]; 

template<class C> inline void clear(C &a) {C().swap(a);}

void dfs(int u, int pre, ll ww) {
	for (auto &e : es[u]) if (e.to ^ pre) {
		int v = e.to; ll w = e.w;
		dfs(v, u, w);
		sum[u] += sum[v];
		if (sum[v] >= 0) {
			H[u].push_back({mi[v], sum[v]});
		} else {
			L[u].push_back({mi[v], sum[v]});
		}
	}
	sort(H[u].begin(), H[u].end());
	sort(L[u].begin(), L[u].end());
	
	ll res = LLONG_MAX, S = 0;
	for (auto &i : H[u]) {
		res = min(res, S + i.a);
		S += i.b;
	}
	for (auto &i : L[u]) {
		res = min(res, S + i.a);
		S += i.b;
	}
	res = min(res, S);
	mi[u] = min(-ww, min(res + a[u] - ww, a[u] + S - 2*ww));
	sum[u] += a[u] - 2*ww;
}

int main() {
	io >> n;
	for (int i = 1; i <= n; ++i) io >> a[i];
	for (int i = 1; i < n; ++i) {
		io >> u >> v >> w;
		es[u].push_back({v, w});
		es[v].push_back({u, w});
	}
	
	dfs(1, 0, 0);
	
	printf("%lld", -mi[1]);
	
	return 0;
}

