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

int n, g[N][N], sz[N], C[N][N], _2[N * N];
vector<vector<int > > f[N];
vector<int > es[N];

inline void dfs(int u, int pre) {
    sz[u] = 1;
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u), sz[u] += sz[v];
    f[u].resize(sz[u] + 1, vector<int >(sz[u] + 1, 0));
    sz[u] = f[u][1][0] = 1;
    for (auto &v : es[u]) if (v ^ pre) {
        For (i, 1, sz[u]) For (j, 0, sz[u] - i) For (k, 0, sz[v]) For (l, 0, sz[v] - k) add(g[i + k][j + l], ml(f[u][i][j], f[v][k][l]));
        vector<vector<int > >().swap(f[v]);
        sz[u] += sz[v];
        For (i, 1, sz[u]) For (j, 0, sz[u] - i) f[u][i][j] = g[i][j], g[i][j] = 0;
    }
    For (i, 1, sz[u]) For (j, 0, sz[u] - i) add(f[u][0][j + 1], ml(f[u][i][j], _2[(i - 1) * (i - 2) / 2]));
}

int main() {
    io >> n;
    For (i, 0, n) C[i][0] = 1;
    For (i, 1, n) For (j, 1, i) C[i][j] = mo(C[i - 1][j - 1] + C[i - 1][j]);
    _2[0] = 1; For (i, 1, n * n) _2[i] = mo(_2[i - 1] << 1);
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs(1, 0);
    rFor (i, n, 1) For (j, i + 1, n) add(f[1][0][i], -ml(f[1][0][j], C[j - 1][i - 1]));
    For (i, 1, n) printf("%d ", f[1][0][i]);

    return 0;
}