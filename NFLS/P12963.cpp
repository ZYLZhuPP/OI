#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, m, K, w[N], inv[N], fac[N], ivf[N], sz[N], lst[N], son[N], Sz[N], ans;
vector<int > es[N];

inline void init() {
    inv[1] = 1; For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1; For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
}

inline int P(int n, int m) { return n>=m? ml(fac[n], ivf[n - m]): 0; }

inline void dfs0(int u, int pre) {
    sz[u] = 1;
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u), sz[u] += sz[v];
}

inline void dfs(int u, int pre) {
    son[pre] = u;
    int v = lst[w[u]];
    if (v) sz[son[v]] -= sz[u]; else Sz[w[u]] += sz[u];
    lst[w[u]] = u;
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u);
    lst[w[u]] = v;
}

int main() {
    freopen("gem.in", "r", stdin);
    freopen("gem.out", "w", stdout);
    init();
    io >> n >> m >> K;
    For (i, 1, n) io >> w[i];
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    dfs(1, 0);
    ans = ml(m, P(n, K));
    For (i, 1, m) add(ans, -P(n - Sz[i], K));
    For (i, 2, n) add(ans, -P(sz[i], K));
    printf("%d", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}
