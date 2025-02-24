#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, ll b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, inv[N], mip[N], pri[N], psz, sz[N], ans = 1;
ll cnt[N], tot;
vector<array<int, 3 > > es[N];
vector<int > d[N];
map<int, int > f[N];

inline void init() {
    inv[1] = 1; For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    For (i, 2, N - 1) {
        if (!mip[i]) pri[mip[i] = ++psz] = i;
        For (j, 1, mip[i]) {
            int x = i * pri[j]; 
            if (x >= N) break;
            mip[x] = j;
        }
    }
}

inline void dfs(int u, int pre) {
    sz[u] = 1;
    for (auto &[v, w, i] : es[u]) if (v ^ pre) {
        dfs(v, u); sz[u] += sz[v]; mul(ans, qPow(w, 1ll * sz[v] * (n - sz[v])));
        for (auto &x : d[i]) {
            int s = sz[v] - f[v][x];
            cnt[x] += 1ll * s * (s - 1) / 2;
            f[v][x] = sz[v];
        }
        if (f[u].size() < f[v].size()) swap(f[u], f[v]);
        for (auto &[x, y] : f[v]) f[u][x] += y;
        f[v].clear();
    }
}

int main() {
    init();
    io >> n; tot = 1ll * n * (n - 1) / 2;
    int u, v, w;
    For (i, 1, n - 1) {
        io >> u >> v >> w;
        es[u].pb({v, w, i}); es[v].pb({u, w, i});
        while (w > 1) {
            int x = mip[w], y = 0;
            while (!(w % pri[x])) w /= pri[x], y++;
            d[i].pb(x);
        }
    }
    dfs(1, 0);
    For (i, 1, psz) {
        int s = n - f[1][i];
        cnt[i] += 1ll * s * (s - 1) / 2;
        mul(ans, qPow(ml(inv[pri[i]], pri[i] - 1), tot - cnt[i]));
    }
    printf("%d", ans);

    return 0;
}
