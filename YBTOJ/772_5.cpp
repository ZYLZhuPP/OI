#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 2e4 + 5, Q = 2e5 + 5, B = 61;
template<class C> inline void cmax(C &x, const C &y) { x = y>x? y: x; }

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

int n, q, x[Q], y[Q], lca[Q];
int dep[N], fa[N], vis[N];
ll w[N];
vector<int > es[N], pt[N];

struct Basis {
    ll o[B]; int pos[B];
    Basis() { memset(o, 0, sizeof o); memset(pos, 0, sizeof pos); }
    void ins(int k, ll x) {
        rFor (i, B - 1, 0) if (x >> i & 1) {
            if (!o[i]) return o[i] = x, pos[i] = k, void();
            if (dep[k] > dep[pos[i]]) swap(k, pos[i]), swap(x, o[i]);
            x ^= o[i];
        }
    }
    ll mx() {
        ll res = 0;
        rFor (i, B - 1, 0) cmax(res, res ^ o[i]);
        return res;
    }
} f[N];

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

void dfs(int u, int pre) {
    vis[u] = 1;
    dep[u] = dep[pre] + 1;
    f[u] = f[pre]; f[u].ins(u, w[u]);
    for (auto &i : pt[u]) {
        int v = x[i] ^ y[i] ^ u;
        if (vis[v]) lca[i] = find(v);
    }
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u), fa[v] = u;
}

int main() {
    io >> n >> q;
    For (i, 1, n) io >> w[i], fa[i] = i;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (i, 1, q) {
        io >> x[i] >> y[i];
        pt[x[i]].pb(i); pt[y[i]].pb(i);
    }
    dfs(1, 0);
    For (i, 1, q) {
        u = x[i], v = y[i]; int fa = lca[i];
        Basis a;
        For (i, 0, B - 1) {
            if (dep[f[u].pos[i]] >= dep[fa]) a.ins(f[u].pos[i], f[u].o[i]);
            if (dep[f[v].pos[i]] >= dep[fa]) a.ins(f[v].pos[i], f[v].o[i]);
        }
        printf("%lld\n", a.mx());
    }

    return 0;
}
