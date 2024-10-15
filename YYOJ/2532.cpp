#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    bool operator ~ () const { return ~c; }
} io;

int n, m, vis[N], ans, pt[5];
vector<array<int, 2 > > es[N];

inline bool ok(int u, int v, int w) {
    for (auto &[x, c] : es[u]) if (v == x && c == w) return 1;
    return 0;
}

inline int solve1() {
    int res = 0;
    For (u, 1, n) {
        for (auto &[v, w] : es[u]) {
            if (vis[v]) {
                res++;
                for (auto &[x, w] : es[v]) if (x ^ u && ok(u, x, 3 - w)) res++;
            }
            vis[v] = w;
        }
        for (auto &[v, w] : es[u]) vis[v] = 0;
    }
    return res >> 1;
}

inline int dfs(int u, int k) {
    pt[k] = u;
    if (k == 4) return ok(pt[1], pt[4], 2) && ((ok(pt[1], pt[2], 2) && ok(pt[3], pt[4], 2)) || (ok(pt[1], pt[3], 2) && ok(pt[2], pt[4], 2)));
    int res = 0;
    vis[u] = 1;
    for (auto &[v, w] : es[u]) if (!vis[v] && w == 1) {
        res += dfs(v, k + 1);
    }
    vis[u] = 0;
    return res;
}

inline int solve2() {
    int res = 0;
    For (i, 1, n) res += dfs(i, 1);
    return res >> 1;
}

int main() {
    io >> n >> m;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, w++, es[u].pb({v, w}), es[v].pb({u, w});
    ans += n;
    ans += solve1();
    ans += solve2();
    printf("%d", ans);

    return 0;
}
