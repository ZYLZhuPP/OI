#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 +5;

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

int n, m, ans, vis[N];
vector<int > es[N], G[N];

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (u, 1, n) for (auto &v : es[u]) if (es[v].size() > es[u].size() || (es[u].size() == es[v].size() && v > u)) G[u].pb(v);
    For (u, 1, n) {
        for (auto &v : G[u]) vis[v] = u;
        for (auto &v : G[u]) for (auto &w : G[v]) if (vis[w] == u) ans++;
    }
    printf("%d", ans);

    return 0;
}
