#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 705, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, m, f[N][N], g[N], h[N], sz[N], C[N][N], _2[N * N], a[N], X, ans[N], inv[N];
vector<int > es[N];

inline void init() {
    For (i, 0, N - 1) C[i][0] = 1;
    For (i, 1, N - 1) For (j, 1, i) C[i][j] = mo(C[i - 1][j - 1] + C[i - 1][j]);
    _2[0] = 1; For (i, 1, N * N - 1) _2[i] = mo(_2[i - 1] << 1);
    inv[1] = 1; For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
}

void dfs(int u, int pre) {
    sz[u] = f[u][1] = 1;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        memset(g, 0, sizeof g);
        For (i, 1, sz[u]) For (j, 0, sz[v]) g[i + j] = (g[i + j] + 1ll * f[u][i] * f[v][j]) % Mo;
        sz[u] += sz[v];
        memcpy(f[u], g, sizeof g);
    }
    For (i, 1, sz[u]) f[u][0] = (f[u][0] + 1ll * X * f[u][i] % Mo * _2[(i - 1) * (i - 2) / 2]) % Mo;
}

int main() {
    freopen("reason.in", "r", stdin);
    freopen("reason.out", "w", stdout);
    init();
    io >> n; m = n + 1;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (i, 1, m) memset(f, 0, sizeof f), X = i, dfs(1, 0), h[i] = f[1][0];
    a[0] = 1; For (i, 1, m) rFor (j, i, 0) a[j] = mo((j? a[j - 1]: 0) - ml(i, a[j]));
    For (i, 1, m) {
        int x = 1;
        For (j, 1, m) if (i ^ j) mul(x, i - j);
        x = ml(h[i], qPow(x, Mo - 2));
        int y = 0;
        For (j, 0, m) {
            y = ml(y - a[j], inv[i]);
            add(ans[j], ml(x, y));
        }
    }
    rFor (i, n, 1) For (j, i + 1, n) add(ans[i], -ml(ans[j], C[j - 1][i - 1]));
    For (i, 1, n) printf("%d ", ans[i]);

    fclose(stdin); fclose(stdout);
    return 0;
}