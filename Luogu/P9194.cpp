#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 4e5 + 5;

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

int n, fa[N], pa[N];
ll s[N], t[N], ans;
vector<int > es[N];

inline void dfs0(int u, int pre) {
    fa[u] = pre; pa[u] = u;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs0(v, u);
        if (u <= n) s[u] += s[v];
        else s[u]++, t[u] += s[v];
    }
}

inline ll F(int i) {
    if (i <= n) return s[i] * s[i];
    ll x = s[i];
    return x * x * x - x * x - x + 2 * x * t[i];
}

inline int find(int x) { return pa[x]^x? pa[x] = find(pa[x]): x; }

int main() {
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(n + i), es[n + i].pb(u), es[v].pb(n + i), es[n + i].pb(v);
    dfs0(n, 0);
    For (i, 1, 2 * n - 1) ans += F(i);
    For (u, 1, n) {
        printf("%lld\n", ans);
        int f = find(fa[u]), g = fa[f], fg = find(fa[g]);
        ans -= F(u) + F(f) + F(g) + F(fg);
        t[fg] -= s[g]; s[g] -= s[f]; s[f]--; t[f] -= s[u];
        for (auto &v : es[u]) if (v ^ fa[u]) {
            pa[v] = f; s[f] += s[v]; t[f] += t[v];
            ans -= F(v);
        }
        s[g] += s[f]; t[fg] += s[g];
        ans += F(f) + F(g) + F(fg);
    }

    return 0;
}
