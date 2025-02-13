#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e4 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

struct IO {
	char c; int f;
#define gc() getchar()
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, L, R, a[N], inq[N], cnt[N];
ll dis[N];
vector<array<int, 2 > > es[N];

inline bool spfa(int rt) {
	queue<int > q;
	dis[rt] = 0; q.push(rt); inq[rt] = 1; cnt[rt] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop(); inq[u] = 0;
		for (auto &[v, w] : es[u]) if (cmax(dis[v], dis[u] + w) && !inq[v]) {
			q.push(v); inq[v] = 1; cnt[v] = cnt[u] + 1;
			if (cnt[v] > n) return 0;
		}
	}
	return 1;
}

int main() {
	io >> n >> L >> R;
	For (i, 1, n) {
		es[i - 1].pb({i, 0});
		io >> a[i];
		if (i > 1) {
			int x = a[i - 1] + a[i];
			int l = L - x, r = R - x;
			es[i - 2].pb({i, l});
			es[i].pb({i - 2, -r});
		}
	}
	memset(dis, -1, sizeof dis);
	if (!spfa(0)) return puts("-1"), 0;
	printf("%lld\n", dis[n]);
	For (i, 1, n) printf("%lld ", a[i] + dis[i] - dis[i - 1]);
	
	return 0;
} 
