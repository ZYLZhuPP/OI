#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

int n, m, U[N], V[N], fa[N], pa[N], dep[N];
ll W[N], val[N];
vector<int > es[N];

inline int find(int x) { return pa[x]^x? pa[x] = find(pa[x]): x; }

inline void dfs0(int u, int pre) {
    dep[u] = dep[pre] + 1; fa[u] = pre;
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u);
}

inline ll query(int u, int v, ll w) {
    while (u ^ v && w) {
        if (dep[u] < dep[v]) swap(u, v);
        w /= val[u];
        u = find(fa[u]);
    }
    return w;
}

int main() {
    io >> n >> m;
    For (i, 1, n) pa[i] = i;
    For (i, 1, n - 1) io >> U[i] >> V[i] >> W[i], es[U[i]].pb(V[i]), es[V[i]].pb(U[i]);
    dfs0(1, 0);
    For (i, 1, n - 1) {
        if (dep[U[i]] < dep[V[i]]) swap(U[i], V[i]);
        val[U[i]] = W[i];
        if (W[i] == 1) pa[U[i]] = find(V[i]);
    }
    int op, u, v, x; ll w;
    while (m--) {
        io >> op;
        if (op == 1) io >> u >> v >> w, printf("%lld\n", query(find(u), find(v), w));
        else {
            io >> x >> w;
            val[U[x]] = w;
            if (w == 1) pa[U[x]] = find(V[x]);
        }
    }

    return 0;
}
