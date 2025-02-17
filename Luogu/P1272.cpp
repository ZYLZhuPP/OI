#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 155;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, p, ans, f[N][N];
vector<int > T[N];

void dfs(int u, int pre) {
    f[u][1] = T[u].size() - (u > 1);
    for (auto &v : T[u]) if (v ^ pre) {
        dfs(v, u);
        rFor (i, p, 2) For (j, 1, i - 1) cmin(f[u][i], f[u][i - j] + f[v][j] - 1);
    }
    cmin(ans, f[u][p] + (u > 1));
}

int main() {
    ans = 500;
    memset(f, 31, sizeof f);
    io >> n >> p;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, T[u].pb(v), T[v].pb(u);
    dfs(1, 0);
    printf("%d", ans);

    return 0;
}