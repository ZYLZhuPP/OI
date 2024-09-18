#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef pair<ll, ll > pa;
#define mkp make_pair
#define st first
#define nd second
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

struct Edge {
	int to;
	ll w;
};
vector<Edge > es[N];

struct Sth {
    ll v, w;
    int cnt;
};
vector<Sth > A;

struct Que {
    ll val, i;
} q[N];

int n, m, u, v;
ll sum, f[N], s[N], w, va[N];
map<pa, int > cnt;

void dfs(int u, int pre) {
	s[u] = 1;
	for (auto &e : es[u]) if (e.to ^ pre) {
		int v = e.to, w = e.w;
		dfs(v, u); s[u] += s[v];
		va[v] = s[v] * (n - s[v]) * w;
        cnt[mkp(s[v], va[v])]++;
		sum += va[v];
	}
}

int main() {
	io >> n >> m;
	For (i, 1, n - 1) {
		io >> u >> v >> w;
		es[u].push_back({v, w});
		es[v].push_back({u, w});
	}
	
	dfs(1, 0);

	for (auto &x : cnt)
        A.push_back({x.st.st, x.st.nd, x.nd});
		
	for (auto &x : A) {
        ll v = x.v, w = x.w, c = x.cnt;
        for (int j = 0; j < v && j <= m; ++j) {
            int l = 1, r = 0;
            for (int i = 0; i * v + j <= m; ++i) {
                int p = i * v + j;
                while (l <= r && q[r].val < f[p] - w * i) --r;
                q[++r] = {f[p] - w * i, i};
                while (l <= r && q[l].i < i - c) ++l;
                f[p] = max(f[p], q[l].val + w * i);
            }
        }
    }
	
	printf("%lld", sum - f[m]);
	
	return 0;
}
