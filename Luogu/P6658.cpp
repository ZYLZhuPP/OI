#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
const int N = 5e5 + 5;

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

int n, m, cnt, vis[N], fa[N], id[N];
ull f[N], g[N];
vector<array<int, 2 > > es[N];
vector<int > pt[N];
unordered_map<ull, int > E;

inline ull rnd() {
    static ull x = 1145141;
    x ^= x << 13; x ^= x >> 17; x ^= x << 7;
    return x;
}

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

inline void dfs(int u, int pre) {
    vis[u] = 1;
    for (auto &[v, id] : es[u]) if (id ^ pre) {
        if (!vis[v]) {
            dfs(v, id), f[u] ^= f[v];
            if (E.count(f[v])) fa[E[f[v]]] = u;
            else fa[v] = u, E[f[v]] = v;
        } else if (!g[id]) {
            g[id] = rnd(); E[g[id]] = 0;
            f[u] ^= g[id]; f[v] ^= g[id];
        }
    }
}

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb({v, i}), es[v].pb({u, i});
    For (i, 1, n) fa[i] = i;
    E[0] = 0;
    For (i, 1, n) {
        if (!vis[i]) dfs(i, 0);
        int f = find(i);
        if (!id[f]) id[f] = ++cnt;
        pt[id[f]].pb(i);
    }
    printf("%d\n", cnt);
    For (i, 1, cnt) {
        for (auto &u : pt[i]) printf("%d ", u);
        puts("");
    }

    return 0;
}
