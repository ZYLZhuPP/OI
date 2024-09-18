#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

int n, d[N], D, p[N], pos, vis[N];
ll tot, f[2][N];
vector<pair<int, int > > G[N];
vector<ll > ans, ins, ers;

struct heap {
	priority_queue<int > q1, q2; ll sum;
	void ins(int x) { q1.push(x); sum += x; }
	void ers(int x) { q2.push(x); sum -= x; }
	void fls() { while (q1.size() && q2.size() && q1.top() == q2.top()) q1.pop(), q2.pop(); }
	int top() { fls(); return q1.top(); }
	void pop() { sum -= top(); q1.pop(); }
	int size() { return q1.size() - q2.size(); }
} H[N];

void mark(int u) {
	for (auto[v, w] : G[u])
		if (d[v] <= D) break; else H[v].ins(w);
}

void dfs(int u, int pre) {
	int del = d[u] - (vis[u] = D);
	while(H[u].size() > del) H[u].pop();
	for (auto[v, w] : G[u]) if (v != pre)
		if (d[v] <= D) break; else dfs(v,u);
	ins.clear(),ers.clear();
	for (auto[v, w] : G[u]) if (v != pre){
		if (d[v] <= D) break;
		ll val = f[0][v] + w - f[1][v]; tot += f[1][v];
		if (val <= 0) tot += val,--del;
		else H[u].ins(val), ins.push_back(val);
	}
	while(H[u].size() && H[u].size() > del) ers.push_back(H[u].top()),H[u].pop();
	f[1][u] = H[u].sum;
	while(H[u].size() && H[u].size() > del - 1) ers.push_back(H[u].top()),H[u].pop();
	f[0][u] = H[u].sum;
	for (int x : ers) H[u].ins(x);
	for (int x : ins) H[u].ers(x);
}

vector<ll> minimum_closure_costs(int N, vector<int > U, vector<int > V, vector<int > W) {
	n = N;
	ans.resize(n);
	For (i, 1, n - 1) {
		int u = U[i - 1] + 1, v = V[i - 1] + 1, w = W[i - 1];
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
		ans[0] += w;
	}
	For (i, 1, n) d[i] = G[i].size(), p[i] = i;
	sort(p + 1, p + n + 1, [](int a, int b) { return d[a] < d[b]; } );
	auto cmp = [](auto a,auto b) { return d[a.first] > d[b.first]; };
	For (i, 1, n) sort(G[i].begin(), G[i].end(), cmp);
	for (D = 1, pos = 1; D < n; ++D) {
	    tot = 0;
		while (pos <= n && d[p[pos]] == D) mark(p[pos++]);
		if (pos > n) break;
		For (j, pos, n) if (vis[p[j]] != D) dfs(p[j], 0), tot += f[1][p[j]];
		ans[D] = tot;
	}
	return ans;
}
