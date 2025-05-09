#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, D = 10, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }

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

int T, n, id[N], dfn[N], dfn_[N], tim, f[N][D][D], g[N][D][D][D], ans, d[N], dp[N][N][D][D];
vector<int > es[N];

inline void init(int n) {
    For (i, 0, 9) For (j, 0, 9) if (i || j) {
        int x = j;
        while (x < 10) x += max(x, i);
        x -= 10;
        f[0][i][j] = x;
    }
    For (i, 1, n) For (j, 0, 9) For (k, 0, 9) {
        int x = k;
        For (l, 0, 9) x = f[i - 1][max(j, l)][x];
        f[i][j][k] = x;
    }
    memset(g, -1, sizeof g);
    For (j, 0, 9) For (k, 0, 9) if (j || k) for (int x = k; x < 10; x += max(x, j)) g[0][j][k][x] = x;
    For (i, 1, n) For (j, 0, 9) For (k, 0, 9) For (l, 0, 9) {
        int x = k;
        For (p, 0, l - 1) x = f[i - 1][max(j, p)][x];
        g[i][j][k][l] = x;
    }
}

inline void dfs(int u) {
    id[dfn[u] = ++tim] = u;
    for (auto &v : es[u]) if (!dfn[v]) dfs(v);
    dfn_[u] = tim;
}

int main() {
    freopen("backgroud.in", "r", stdin);
    freopen("backgroud.out", "w", stdout);
    init(500);
    io >> T;
    while (T--) {
        io >> n;
        ans = tim = 0;
        For (i, 1, n) dfn[i] = 0, es[i].resize(0);
        int u, v;
        For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
        For (i, 1, n) io >> d[i], sort(es[i].begin(), es[i].end());
        dfs(1);
        For (i, 1, n) dp[0][i][0][1] = 1;
        For (i, 1, n) {
            int x = d[id[i]];
            For (j, 1, n - i + 1) For (k, 0, 9) For (l, 0, 9) if (dp[i - 1][j][k][l]) {
                if (~g[j - 1][k][l][x]) add(dp[i][j - 1][max(k, x)][g[j - 1][k][l][x]], dp[i - 1][j][k][l]);
                if (i > 1) add(dp[dfn_[id[i]]][j][k][l], dp[i - 1][j][k][l]);
            }
            For (k, 0, 9) For (l, 0, 9) add(ans, dp[i][0][k][l]);
        }
        printf("%d\n", ans);
        For (i, 0, n) For (j, 0, n) For (k, 0, 9) For (l, 0, 9) dp[i][j][k][l] = 0;
    }

    fclose(stdin); fclose(stdout);
    return 0;
}
