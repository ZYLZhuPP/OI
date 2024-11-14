#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5, Mo = 1e9 + 7;
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

int n, f[N][4][3], g[4][3];
vector<int > es[N];

inline void dfs(int u, int pre) {
    f[u][0][0] = f[u][0][1] = 1;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        For (i, 0, 3) For (j, 0, 2) g[i][j] = f[u][i][j];
        For (i, 0, 3) For (j, 0, 2) if (g[i][j]) For (k, 0, 3 - i) For (l, 0, min(1, 2 - j)) if (k || l) add(f[u][i + k][j + l], ml(g[i][j], f[v][k][l]));
    }
    For (i, 0, 2) add(f[u][i + 1][0], f[u][i][2]);
}

int main() {
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs(1, 0);
    printf("%d", f[1][3][0]);

    return 0;
}
