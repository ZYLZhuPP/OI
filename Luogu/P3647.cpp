#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, inf = 1e9;

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

int n, ans, f[N][2], son1[N], son2[N], mx1[N], mx2[N];
int g[N][2], k[N][2], val[N];
vector<pair<int, int > > G[N];

void dfs(int u, int pre) {
    f[u][0] = 0; f[u][1] = -inf;
    mx1[u] = mx2[u] = -inf; son1[u] = son2[u] = 0;
    for (auto &[v, w] : G[u]) if (v ^ pre) {
        val[v] = w; dfs(v, u);
        f[u][0] += max(f[v][0], f[v][1] + w);
    }
    for (auto &[v, w] : G[u]) if (v ^ pre) {
        int val = f[v][0] + w - max(f[v][0], f[v][1] + w);
        if (val > mx1[u]) swap(son1[u], son2[u]), swap(mx1[u], mx2[u]), mx1[u] = val, son1[u] = v;
        else if (val > mx2[u]) son2[u] = v, mx2[u] = val;
    }
    f[u][1] = f[u][0] + mx1[u];
} 
void solve(int u, int pre) {
    for (auto &[v, w] : G[u]) if (v ^ pre) {
        if (son1[u] == v) swap(son1[u], son2[u]), swap(mx1[u], mx2[u]);
        k[u][0] = g[u][0] - max(f[v][0], f[v][1] + w);
        k[u][1] = k[u][0] + mx1[u];
        if (pre) k[u][1] = max(k[u][1], k[u][0] + k[pre][0] + val[u] - max(k[pre][0], k[pre][1] + val[u]));
        g[v][0] = f[v][0] + max(k[u][0], k[u][1] + w);
        if (mx1[u] < mx2[u]) swap(mx1[u], mx2[u]), swap(son1[u], son2[u]);
        solve(v, u);
    }
}
int main() {
    io >> n;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, G[u].pb({v, w}), G[v].pb({u, w});
    dfs(1, 0);
    g[1][0] = f[1][0];
    solve(1, 0);
    For (i, 1, n) ans = max(ans, g[i][0]);
    printf("%d", ans);

    return 0;
}
