#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef __int128 lll;
const int N = 1e5 + 5;

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

int n, b[N], c[N], d[N], fa[N], vis[N];
ll a[N];
array<int, 2 > t[N];
vector<int > es[N];

inline void dfs0(int u, int pre) {
    fa[u] = pre;
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u);
}

inline lll S(int i, int x) {
    if (x < 1) return 0;
    int res = x>d[i]? x - d[i]: 0;
    if (res) x = d[i];
    return res + 1ll * x * b[i] + (lll)x * (x + 1) / 2 * c[i];
}

inline int calc(int i, int R) {
    lll x = S(i, R);
    if (x < a[i]) return -1;
    int l = 0, r = R, res = -1;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (x - S(i, m) >= a[i]) res = m, l = m + 1;
        else r = m - 1;
    }
    return res;
}

inline bool ok(int r) {
    For (i, 1, n) if (!(t[i][0] = calc(i, r) + 1)) return 0; else t[i][1] = i, vis[i] = 0;
    sort(t + 1, t + n + 1);
    int T = 0;
    For (i, 1, n) {
        int u = t[i][1];
        if (vis[u]) continue;
        while (u && !vis[u]) vis[u] = 1, u = fa[u], T++;
        if (T > t[i][0]) return 0;
    }
    return 1;
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i] >> b[i] >> c[i], d[i] = c[i]<0? (b[i] - 1) / (-c[i]): 1e9;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    int l = n, r = 1e9, ans = 1e9;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (ok(m)) ans = m, r = m - 1;
        else l = m + 1;
    }
    printf("%d", ans);

    return 0;
}
