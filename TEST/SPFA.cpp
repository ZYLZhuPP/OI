#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e16;
const int N = 3e4 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, m, s, inq[N];
ll dis[N];
vector<pair<int, int > > G[N];

inline void SPFA(int rt) {
    queue<int > q;
    For (i, 1, n) dis[i] = INF;
    dis[rt] = 0, q.push(rt), inq[rt] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for (auto &[v, w] : G[u]) if (cmin(dis[v], dis[u] + w) && !inq[v]) q.push(v), inq[v] = 1;
    }
}

int main() {
    io >> n >> m >> s;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, G[u].pb({v, w});
    SPFA(s);
    For (i, 1, n) if (dis[i] < INF) printf("%lld\n", dis[i]); else puts("NO PATH");

    return 0;
}
