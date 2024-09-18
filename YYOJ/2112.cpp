#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e5 + 5, lgN = 22;

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int n, num, x, y, z, ans, dep[N], u, fa[N][lgN];

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 20, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 20, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
int dist(int x, int y, int u) {
    int f = lca(x, y), fx = lca(x, u), fy = lca(y, u);
    return fx==fy? (dep[u] + dep[f] - 2 * dep[fx]): (dep[u] - dep[fx + fy - f]);
}

int solve(int u) {
    For (i, 1, 20) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    if (dis(u, x) < dis(u, y)) swap(x, y);
    if (dis(u, x) > dis(x, y)) swap(u, y);
    if (dist(x, y, u) > dist(x, y, z)) swap(z, u);
    return dis(x, y) + max(dist(x, y, z) - 1, 0);
}

int main() {
    io >> num;
    io >> n;
    dep[x = y = z = 1] = 1;
    For (i, 2, n) {
        io >> u; u ^= ans;
        fa[i][0] = u; dep[i] = dep[u] + 1;
        printf("%d\n", ans = solve(i));
    }

    return 0;
}
