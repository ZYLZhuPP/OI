#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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

int n, a[N], sz[N], son[N], cnt[N], mx;
ll s[N], ans[N];
vector<int > es[N];

inline void dfs0(int u, int pre) {
    sz[u] = 1;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs0(v, u); sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

inline void upd(int u, int pre, const int &d) {
    s[cnt[a[u]]] -= a[u]; if (!s[mx]) mx--;
    s[cnt[a[u]] += d] += a[u]; cmax(mx, cnt[a[u]]);
    for (auto &v : es[u]) if (v ^ pre) upd(v, u, d);
}

inline void dfs(int u, int pre) {
    for (auto &v : es[u]) if (v ^ pre && v ^ son[u]) dfs(v, u), upd(v, u, -1);
    if (son[u]) dfs(son[u], u);
    for (auto &v : es[u]) if (v ^ pre && v ^ son[u]) upd(v, u, 1);
    s[cnt[a[u]]] -= a[u]; s[++cnt[a[u]]] += a[u];
    cmax(mx, cnt[a[u]]);
    ans[u] = s[mx];
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    dfs(1, 0);
    For (i, 1, n) printf("%lld ", ans[i]);

    return 0;
}
