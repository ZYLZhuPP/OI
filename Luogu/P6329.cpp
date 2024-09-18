#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef vector<int > vec;
const int N = 1e5 + 5;
inline void cmax(int &x, const int &y) { x = y>x? y: x; }

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, val[N], m, ans;
vec T[N];

namespace BIT {
    vec o[2][N];
#define lowbit(x) ((x) & -(x))
    inline void upd(vec &o, int x, int d) {
        for (x++; x < (int)o.size(); x += lowbit(x)) o[x] += d;
    }
    inline int query(vec &o, int x) {
        int r = 0;
        for (x = min(x + 1, (int)o.size() - 1); x > 0; x -= lowbit(x)) r += o[x];
        return r;
    }
}
using namespace BIT;

namespace D {
    int dep[N], fa[N][20];
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        rFor (i, 19, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
        if (u == v) return u;
        rFor (i, 19, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
    }
    int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
}
using namespace D;

namespace VD {
    int Fa[N], sz[N], msz[N], vis[N];
    int getG(int u, int pre, int n) {
        msz[u] = 0;
        for (auto v : T[u]) if (!vis[v] && v ^ pre) {
            cmax(msz[u], sz[v]);
            if (v = getG(v, u, n)) {
                sz[u] = n - msz[u];
                return v;
            }
        }
        return max(msz[u], n - sz[u]) <= n / 2? sz[u] = n, u: 0;
    }
    void Divide(int u, int pre) {
        u = getG(u, 0, sz[u]); vis[u] = 1; Fa[u] = pre;
        o[0][u].resize(sz[u] + 2); o[1][u].resize(sz[u] + 2);
        for (auto &v : T[u]) if (!vis[v]) Divide(v, u);
    }
}
using namespace VD;

void init(int u, int pre) {
    sz[u] = 1; dep[u] = dep[pre] + 1; fa[u][0] = pre;
    For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &v : T[u]) if (v ^ pre) init(v, u), sz[u] += sz[v];
}

void Upd(int rt, int d) {
    for (int u = rt; u; u = Fa[u]) upd(o[0][u], dist(u, rt), d);
    for (int u = rt; Fa[u]; u = Fa[u]) upd(o[1][u], dist(Fa[u], rt), d);
}

int Query(int rt, int d) {
    int res = query(o[0][rt], d);
    for (int u = rt; Fa[u]; u = Fa[u]) {
        int x = dist(Fa[u], rt);
        res += query(o[0][Fa[u]], d - x) - query(o[1][u], d - x);
    }
    return res;
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> val[i];
    int u, v;
    For (i, 1, n - 1) io >> u >> v, T[u].pb(v), T[v].pb(u);
    init(1, 0);
    Divide(1, 0);
    For (i, 1, n) Upd(i, val[i]);
    while (m--) {
        int op, x, y;
        io >> op >> x >> y; x ^= ans; y ^= ans;
        if (op == 0) printf("%d\n", ans = Query(x, y));
        else if (op == 1) Upd(x, y - val[x]), val[x] = y;
    }

    return 0;
}
