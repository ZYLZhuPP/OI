#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e4 + 5;
inline void cmax(int &x, const int &y) { x = y>x? y: x; }

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

int n, k;

namespace VD {
    struct Edge { int to, w; };
    vector<Edge > es[N];
    int vis[N], siz[N], msz[N], dis[N];
    void init(int u, int pre) { siz[u] = 1; for (auto &e : es[u]) if (e.to ^ pre) init(e.to, u), siz[u] += siz[e.to]; }
    int getG(int u, int pre, int n) {
        msz[u] = 0;
        for (auto &e : es[u]) if (!vis[e.to] && e.to ^ pre) {
            int v = e.to;
            cmax(msz[u], siz[v]);
            if (v = getG(v, u, n)) {
                siz[u] = n - msz[u];
                return v;
            }
        }
        return max(msz[u], n - siz[u]) <= n / 2? u: 0;
    }
    vector<int > o;
    void dfs(int u, int pre) {
        o.pb(dis[u]);
        for (auto &e : es[u]) if (!vis[e.to] && e.to ^ pre) {
            int v = e.to;
            dis[v] = dis[u] + e.w;
            dfs(v, u);
        }
    }
    int calc(int u, int d) {
        dis[u] = d; o.resize(0);
        dfs(u, 0);
        sort(o.begin(), o.end());
        int n = o.size(), r = n - 1, res = 0;
        For (i, 0, r) {
            while (r > i && o[i] + o[r] > k) r--;
            res += r - i;
        }
        return res;
    }
    int Divide(int u) {
        u = getG(u, 0, siz[u]); vis[u] = 1;
        int res = calc(u, 0);
        for (auto &e : es[u]) if (!vis[e.to]) {
            res -= calc(e.to, e.w);
            res += Divide(e.to);
        }
        return res;
    }
}
using namespace VD;

int main() {
    io >> n;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    io >> k;
    init(1, 0);
    cout << Divide(1);

    return 0;
}
