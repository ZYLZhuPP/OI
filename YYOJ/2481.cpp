#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 998244353;
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

int n, sz[N], inv[N], f[N];
vector<int > es[N];

inline void dfs0(int u, int pre) {
    sz[u] = 1;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs0(v, u), sz[u] += sz[v];
        int x = n - sz[v];
        add(f[v], ml(x, inv[x + 1]));
    }
    int x = ml(sz[u], inv[sz[u] + 1]);
    add(f[1], x);
    add(f[u], -x);
}

inline void dfs(int u, int pre) {
    add(f[u], f[pre]);
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u);
}

inline void init() {
    inv[1] = 1;
    For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
}

int main() {
    init();
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    dfs(1, 0);
    int x = 1;
    For (i, 1, n - 1) mul(x, i);
    int y = ml(x, n);
    mul(x, n - 1);
    For (i, 1, n) printf("%d\n", mo(ml(f[i], y) + x));

    return 0;
}
