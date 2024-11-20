#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

int n, q, ans[N];

namespace VD {
    int sz[N], msz[N], cnt[N], be[N], vis[N];
    set<pair<int, int > > a[N], b[N];
    vector<array<int, 2 > > es[N];
    vector<array<int, 3 > > qs[N];
    inline void init(int u, int pre) { sz[u] = 1; for (auto &[v, w] : es[u]) if (v ^ pre) init(v, u), sz[u] += sz[v]; }
    inline int getG(int u, int pre, int n) {
        msz[u] = 0;
        for (auto [v, w] : es[u]) if (!vis[v] && v ^ pre) {
            cmax(msz[u], sz[v]);
            v = getG(v, u, n);
            if (v) return sz[u] = n - msz[u], v;
        }
        return max(n - sz[u], msz[u]) <= n / 2? sz[u] = n, u: 0;
    }
    inline void dfs(int u, int pre, int rt) {
        be[u] = rt;
        for (auto &[d, v] : b[u]) a[u].insert({d, v}), cnt[v] = 0, be[v] = rt;
        for (auto &[v, w] : es[u]) if (!vis[v] && v ^ pre) {
            dfs(v, u, rt? rt: v);
            if (!a[v].empty()) a[u].insert({a[v].begin()->first + w, a[v].begin()->second}), a[v].clear();
        }
        if (!a[u].empty()) cnt[a[u].begin()->second]++;
    }
    inline void Divide(int u) {
        int G = getG(u, 0, sz[u]); vis[G] = 1;
        swap(qs[u], qs[G]);
        dfs(G, 0, 0);
        for (auto &[s, t, id] : qs[G]) if (!be[s] || !be[t] || be[s] ^ be[t]) ans[id] += cnt[s];
        if (!a[G].empty()) {
            auto [d, x] = *a[G].begin();
            for (auto &[s, t, id] : qs[G]) if (be[s] && be[t] && be[s] ^ be[t] && be[x] == be[t] && s ^ x) {
                auto it = next(a[G].begin());
                if (it != a[G].end() && it->second == s) ans[id]++;
            }
            for (auto &[v, w] : es[G]) if (!vis[v]) {
                if (be[x] ^ v) b[v].insert({d + w, x});
                else {
                    auto it = next(a[G].begin());
                    if (it != a[G].end()) b[v].insert({it->first + w, it->second});
                }
            }
        }
        a[G].clear(); b[G].clear();
        for (auto &[s, t, id] : qs[G]) if (be[t]) if (be[s] == be[t] || b[be[t]].begin()->second == s) qs[be[t]].pb({s, t, id});
        qs[G].resize(0);
        for (auto &[v, w] : es[G]) if (!vis[v]) Divide(v);
    }
}
using namespace VD;

int main() {
    io >> n;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    For (i, 1, n) if (es[i].size() == 1) b[i].insert({0, i});
    io >> q;
    int s, t;
    For (i, 1, q) io >> s >> t, qs[1].pb({s, t, i});
    init(1, 0);
    Divide(1);
    For (i, 1, q) printf("%d\n", ans[i]);

    return 0;
}
