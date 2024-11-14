#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

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

int n, fa[N];
ll f[N][30], ans[N];
vector<int > es[N];

inline void dfs(int u, int pre) {
    fa[u] = pre;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        For (i, 1, 29) f[u][i - 1] += f[v][i];
        For (i, 2, 29) f[v][i - 2] -= f[v][i];
    }
}

int main() {
    io >> n;
    For (i, 1, n) {
        io >> f[i][0];
        For (j, 1, 29) f[i][j] = f[i][j - 1] >> 1;
    }
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs(1, 0);
    For (i, 1, n) for (int u = i, j = 0; u && j <= 29; u = fa[u], ++j) ans[i] += f[u][j];
    For (i, 1, n) printf("%lld ", ans[i]);

    return 0;
}
