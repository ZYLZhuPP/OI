#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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
	inline bool operator ~ () const { return ~c; }
} io;

struct Edge { int to, w; };
vector<Edge > T[N];

int n, Q, s[N];
ll s1[N], s2[N];

namespace VD {
    int sz[N], msz[N], Fa[N], son[N], vis[N];
    unordered_map<int, int > dis[N];
    vector<int > DT[N];
    void init(int u, int pre) { sz[u] = 1; for (auto &[v, w] : T[u]) if (v ^ pre) init(v, u), sz[u] += sz[v]; }
    int getG(int u, int pre, int n) {
        msz[u] = 0;
        for (auto [v, w] : T[u]) if (!vis[v] && v ^ pre) {
            msz[u] = max(msz[u], sz[v]);
            if (v = getG(v, u, n)) {
                sz[u] = n - msz[u];
                return v;
            }
        }
        return max(msz[u], n - sz[u]) <= n / 2? sz[u] = n, u: 0;
    }
    void dfs(int u, int pre, int rt) {
        for (auto &[v, w] : T[u]) if (!vis[v] && v ^ pre) {
            dis[rt][v] = dis[rt][u] + w;
            dfs(v, u, rt);
        }
    }
    void Divide(int u, int pre) {
        int v = getG(u, 0, sz[u]); son[v] = u; u = v;
        vis[u] = 1; Fa[u] = pre; DT[pre].pb(u);
        dis[u][u] = 0; dfs(u, 0, u);
        for (auto &[v, w] : T[u]) if (!vis[v]) Divide(v, u);
    }
}
using namespace VD;

void Upd(int u, int d) {
    for (int v = u; v; v = Fa[v]) s[v] += d, s1[v] += 1ll * dis[v][u] * d;
    for (int v = u; Fa[v]; v = Fa[v]) s2[v] += 1ll * dis[Fa[v]][u] * d;
}

ll Query(int u) {
    ll res = s1[u];
    for (int v = u; Fa[v]; v = Fa[v])
        res += s1[Fa[v]] - s2[v] + 1ll * dis[Fa[v]][u] * (s[Fa[v]] - s[v]);
    return res;
}

ll solve(int u) {
    ll res = Query(u);
    for (auto &v : DT[u]) if (Query(son[v]) < res) return solve(v);
    return res;
}

int main() {
    io >> n >> Q;
    int u, v, w, d;
    For (i, 1, n - 1) io >> u >> v >> w, T[u].pb({v, w}), T[v].pb({u, w});
    init(1, 0); int G = getG(1, 0, n);
    init(1, 0); Divide(1, 0);

    while (Q--) {
        io >> u >> d;
        Upd(u, d);
        printf("%lld\n", solve(G));
    }

    return 0;
}
