#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e6 + 5, Mo = 998244353;
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

int n, a[N], b[N], inv[N], fac[N], ivf[N], f[N], ans, sz[N];

inline void init() {
    inv[1] = 1;
    For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1;
    For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
}

inline void dfs0(int u) {
    if (!u) return;
    dfs0(a[u]); dfs0(b[u]);
    sz[u] = sz[a[u]] + sz[b[u]] + 1;
}

inline void dfs(int u, int x) {
    if (!u) return;
    if (sz[a[u]] <= sz[b[u]]) For (i, 0, sz[a[u]] - 1) add(ans, ml(x, ml(f[i], f[sz[u] - 1 - i])));
    else {
        add(ans, ml(x, f[sz[u]]));
        For (i, 0, sz[b[u]]) add(ans, -ml(x, ml(f[i], f[sz[u] - 1 - i])));
    }
    dfs(a[u], ml(x, f[sz[b[u]]]));
    dfs(b[u], x);
}

int main() {
    init();
    io >> n;
    For (i, 1, n) io >> a[i] >> b[i];
    For (i, 0, n) f[i] = ml(fac[2 * i], ml(ivf[i], ivf[i + 1]));
    For (i, 1, n - 1) add(ans, f[i]);
    dfs0(1);
    dfs(1, 1);
    printf("%d", ans);

    return 0;
}
