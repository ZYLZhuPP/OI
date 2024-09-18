#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int n, m, f[N][2], g[N][2], x[N], y[N], cnt, ans, pd[N][2];
vector<int > T[N];

struct P {
    int x, y;
    inline P operator + (const P &a) const { return {mo(x + a.x), mo(y + a.y)}; }
    inline P operator * (const int &a) const { return {ml(x, a), ml(y, a)}; }
} k[N][2], to[N][2];

namespace VT {
    int is[N], dfn[N], tim, siz[N], vis[N];
    vector<int > es[N];
    bool dfs(int u, int pre) {
        dfn[u] = ++tim;
        int ret = 0;
        for (auto &v : es[u]) if (v ^ pre) {
            if (!dfn[v]) ret += dfs(v, u);
            else { is[u] = 1; if (dfn[u] < dfn[v]) x[++cnt] = u, y[cnt] = v; }
        }
        is[u] |= ret >= 2;
        return ret || is[u];
    }
    int build(int u) {
        g[u][0] = g[u][1] = 1; vis[u] = 1;
        int pos = 0;
        for (auto &v : es[u]) if (!vis[v]) {
            int x = build(v);
            if (!x) {
                mul(g[u][0], mo(g[v][0] + g[v][1]));
                mul(g[u][1], g[v][0]);
            } else if (is[u]) {
                T[u].pb(x);
                to[x][0] = k[v][0] + k[v][1];
                to[x][1] = k[v][0];
            } else {
                pos = x;
                k[u][0] = k[v][0] + k[v][1];
                k[u][1] = k[v][0];
            }
        }
        if (is[u]) k[u][0] = {1, 0}, k[u][1] = {0, 1}, pos = u;
        else k[u][0] = k[u][0] * g[u][0], k[u][1] = k[u][1] * g[u][1];
        return pos;
    }
}
using namespace VT;

void solve(int u) {
    f[u][0] = !pd[u][1] * g[u][0];
    f[u][1] = !pd[u][0] * g[u][1];
    for (auto &v : T[u]) {
        solve(v);
        mul(f[u][0], mo(ml(to[v][0].x, f[v][0]) + ml(to[v][0].y, f[v][1])));
        mul(f[u][1], mo(ml(to[v][1].x, f[v][0]) + ml(to[v][1].y, f[v][1])));
    }
}

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
    is[1] = 1; dfs(1, 0);
    build(1);
    For (s, 0, (1 << cnt) - 1) {
        For (i, 1, cnt)
            if (s >> (i - 1) & 1) pd[x[i]][1] = pd[y[i]][0] = 1;
            else pd[x[i]][0] = 1;
        solve(1);
        add(ans, mo(f[1][0] + f[1][1]));
        For (i, 1, cnt) pd[x[i]][0] = pd[x[i]][1] = pd[y[i]][0] = 0;
    }
    printf("%d", ans);

    return 0;
}
