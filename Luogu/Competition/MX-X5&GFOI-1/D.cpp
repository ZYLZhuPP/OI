#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, q, pt[55], a[N];
bool vis[N];
ll ans = 1e18, dis[55][N];
vector<array<int, 2 > > es[N];

inline int id(int x, int y) { return (x - 1) * m + y; }

int main() {
    io >> n >> m >> q;
    For (i, 1, n) For (j, 1, m) io >> a[id(i, j)];
    For (i, 1, n) For (j, 1, m) {
        if (i < n) {
            int x = a[id(i, j)] + a[id(i + 1, j)];
            if (x < 0) return puts("No"), 0;
            es[id(i, j)].pb({id(i + 1, j), x});
            es[id(i + 1, j)].pb({id(i, j), x});
        }
        if (j < m) {
            int x = a[id(i, j)] + a[id(i, j + 1)];
            if (x < 0) return puts("No"), 0;
            es[id(i, j)].pb({id(i, j + 1), x});
            es[id(i, j + 1)].pb({id(i, j), x});
        }
    }
    int x, y;
    For (i, 1, q) io >> x >> y, pt[i] = id(x, y);
    memset(dis, 31, sizeof dis);
    For (i, 1, q) {
        memset(vis, 0, sizeof vis);
        dis[i][pt[i]] = 0;
        priority_queue<pair<ll, int> > q;
        q.push({0, pt[i]});
        while (!q.empty()) {
            int u = q.top().nd; q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto &[v, w] : es[u]) if (!vis[v] && cmin(dis[i][v], dis[i][u] + w)) q.push({-dis[i][v], v});
        }
    }
    For (i, 1, n * m) {
        ll res = -1e18;
        For (j, 1, q) cmax(res, dis[j][i] + a[pt[j]] + a[i]);
        cmin(ans, res / 2);
    }
    printf("%lld", ans);

    return 0;
}
