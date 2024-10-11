#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, sz[N], msz[N], G, cnt[N], co[N], color;
ll ans;
vector<array<int, 2 > > es[N];
set<int > pt[N], mn;
set<pair<int, int > > mx;

inline void dfs0(int u, int pre) {
    sz[u] = 1;
    for (auto &[v, w] : es[u]) if (v ^ pre) dfs0(v, u), cmax(msz[u], sz[v]), sz[u] += sz[v];
    if (max(n - sz[u], msz[u]) <= n / 2) G = u;
}

inline void dfs1(int u, int pre) {
    sz[u] = 1; co[u] = pre^G? co[pre]: ++color; cnt[co[u]] += 2; pt[co[u]].insert(u);
    for (auto &[v, w] : es[u]) if (v ^ pre) dfs1(v, u), sz[u] += sz[v], ans += 2ll * sz[v] * w;
}

int main() {
    io >> n;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    dfs0(1, 0);
    dfs1(G, 0);
    printf("%lld\n", ans);
    For (i, 0, color) mx.insert({cnt[i], i}), mn.insert(*pt[i].begin());
    For (i, 1, n) {
        int x = co[i];
        auto a = mn.begin();
        auto [c, b] = *mx.rbegin();
        int y = b&&c==n-i+1&&b^x? b: (!co[*a]||co[*a]^x? co[*a]: co[*++a]);
        int z = *pt[y].begin();
        printf("%d ", z); pt[y].erase(z); mn.erase(z);
        if (!pt[y].empty()) mn.insert(*pt[y].begin());
        mx.erase({cnt[x], x}); mx.insert({--cnt[x], x});
        mx.erase({cnt[y], y}); mx.insert({--cnt[y], y});
    }

    return 0;
}
