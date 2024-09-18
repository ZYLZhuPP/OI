#include<bits/stdc++.h>
using namespace std;

#define mkp make_pair
#define st first
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
template<class C> inline void clear(C &a) { C().swap(a); }
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
	inline bool operator ~() {return ~c;}
} io;

int T, n, rt;
vector<int > es[N], ans;
vector<pair<int, int > > mi[N];

void dfs(int u, int pre) {
	for (auto &v : es[u]) if (v ^ pre) {
		dfs(v, u);
		if (mi[v].size()) mi[u].push_back(mkp(mi[v][0].st, v));
		else mi[u].push_back(mkp(v, v));
	}
	sort(mi[u].begin(), mi[u].end());
}

void solve(int u, bool RT) {
	if (RT) {
		for (auto &e : mi[u]) solve(e.nd, 1);
		ans.push_back(u);
		return;
	}
	
	int s = mi[u].size();
	if (!s) ans.push_back(u);
	else if (mi[u][s - 1].st > u) {
		For (i, 0, s - 2) solve(mi[u][i].nd, 1);
		ans.push_back(u);
		solve(mi[u][s - 1].nd, 0);
	} else {
		for (auto &e : mi[u]) solve(e.nd, 1);
		ans.push_back(u);
	}
}

int main() {
	io >> T;
	while (T--) {
		clear(ans);
		io >> n;
		For (i, 1, n) clear(es[i]), clear(mi[i]);
		int u, v;
		For (i, 1, n - 1) {
			io >> u >> v;
			es[u].push_back(v);
			es[v].push_back(u);
		}
		
		rt = n + 1;
		For (i, 1, n) if (es[i].size() <= 1) rt = min(rt, i);
		
		dfs(rt, 0);
		solve(rt, 0);
		
		int s = ans.size();
		For (i, 0, s - 2) printf("%d ", ans[i]);
		printf("%d\n", ans[s - 1]);
	}
	
	return 0;
} 
