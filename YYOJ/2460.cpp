#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i   )
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int n, m, q, T, op[N], u[N], v[N], x[N], y[N], fa[N], vis[N], tim, id[N], rt[N], sz[N];
bool no[N], ans[N];

inline int find(int fa[], int x) { return fa[x]^x? fa[x] = find(fa, fa[x]): x; }

inline int& Fa(int u) { return fa[u] = find(id, fa[u]); }

inline void makert(int u) {
    int v = 0;
    while (u) {
        swap(v, Fa(u));
        swap(u, v);
    }
}

inline int lca(int u, int v) {
    tim++;
    while (u | v) {
        if (u) {
            if (vis[u] == tim) return u;
            vis[u] = tim, u = Fa(u);
        }
        swap(u, v);
    }
    return 0;
}

inline void merge(int u, int f, int rt) {
    while (u ^ f) {
        sz[rt]--;
        id[u] = f;
        u = Fa(u);
    }
}

inline void link(int u, int v) {
    u = find(id, u); v = find(id, v);
    if (u == v) return;
    int fu = find(rt, u), fv = find(rt, v);
    if (fu ^ fv) {
        if (sz[fu] < sz[fv]) swap(u, v), swap(fu, fv);
        makert(v);
        fa[v] = u; sz[fu] += sz[fv]; rt[fv] = fu;
    } else {
        int f = lca(u, v);
        merge(u, f, fu); merge(v, f, fv);
    }
}

int main() {
    io >> n >> m >> q >> T;
    For (i, 1, m) io >> u[i] >> v[i];
    For (i, 1, q) {
        io >> op[i];
        if (op[i] == 1) io >> x[i], no[x[i]] = 1;
        else io >> x[i] >> y[i];
    }
    For (i, 1, n) id[i] = rt[i] = i, sz[i] = 1;
    For (i, 1, m) if (!no[i]) link(u[i], v[i]);
    rFor (i, q, 1) {
        if (op[i] == 1) link(u[x[i]], v[x[i]]);
        else ans[i] = find(id, x[i]) == find(id, y[i]);
    }
    For (i, 1, q) if (op[i] == 2) puts(ans[i]? "YES": "NO");

    return 0;
}
