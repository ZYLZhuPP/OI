#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int n, f[N][2], cnt[N], ans[N], now;
vector<int > es[N];

inline void dfs(int u, int pre) {
    int g[3] = {1, 0, 0};
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        mul(g[2], f[v][0]); add(g[2], ml(g[1], f[v][1]));
        mul(g[1], f[v][0]); add(g[1], ml(g[0], f[v][1]));
        mul(g[0], f[v][0]);
    }
    f[u][0] = mo(g[0] + g[2]); f[u][1] = g[1];
    if ((int)es[u].size() >= now) add(f[u][0], mo(g[0] + g[1])), add(f[u][1], g[0]);
}

int main() {
    freopen("degree.in", "r", stdin);
    freopen("degree.out", "w", stdout);
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (i, 1, n) cnt[es[i].size()]++;
    int res = 1;
    rFor (i, n - 1, 1) now = i, res = ans[i] = cnt[i]? dfs(1, 0), f[1][0]: res;
    For (i, 1, n - 1) printf("%d\n", ans[i]);

    fclose(stdin); fclose(stdout);
    return 0;
}
