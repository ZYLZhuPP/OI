#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 1e9 + 7;
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

int T, id, n, K, imp[N], f[N][2], d[N], inv[N], ans;
vector<array<int, 2 > > es[N];

inline void dfs(int u, int pre) {
    int x = 0;
    for (auto &[v, id] : es[u]) if (v ^ pre) {
        dfs(v, u);
        if (imp[id]) add(f[v][1], f[v][0]), f[v][0] = 0;
        add(x, ml(f[u][0] + f[u][1], f[v][0] + f[v][1]) - ml(f[u][0], f[v][0]));
        add(f[u][0], f[v][0]); add(f[u][1], f[v][1]);
    }
    int y = inv[d[u]];
    add(ans, ml(x, y));
    if (!d[u]) add(f[u][0], 1);
    mul(f[u][0], y); mul(f[u][1], y);
}

inline void init() {
    inv[0] = inv[1] = 1; For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
}

int main() {
    init();
    io >> id >> T;
    while (T--) {
        io >> n >> K;
        For (i, 1, n) d[i] = -1, es[i].resize(0), f[i][0] = f[i][1] = imp[i] = 0;
        int u, v, x;
        For (i, 1, n - 1) io >> u >> v, es[u].pb({v, i}), es[v].pb({u, i}), d[u]++, d[v]++;
        For (i, 1, K) io >> x, imp[x] = 1;
        if (n == 2) { puts("1"); continue; }
        ans = 0;
        For (i, 1, n) if (d[i]) { dfs(i, 0); break; }
        For (i, 1, n) For (j, 1, d[i]) mul(ans, j);
        printf("%d\n", ans);
    }

    return 0;
}
