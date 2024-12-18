#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, inf = 1e9;

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

int n, fa[N], dfn[N], tim, key[N], ans[N];
char a[N];
vector<int > es[N];

struct P {
    int x, c;
    inline bool operator < (const P &a) const { return x^a.x? x<a.x: c<a.c; }
    inline P operator + (const int &k) const { return {x + k, c + 1}; }
    inline P& operator += (const P &a) { x += a.x, c += a.c; return *this; }
} f[N][2];

inline void dfs0(int u, int pre) {
    dfn[u] = ++tim; key[tim] = a[u] & 1; fa[tim] = dfn[pre];
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u);
}

inline void calc(int k) {
    For (i, 1, n) f[i][0] = {key[i] * inf, 0}, f[i][1] = {1, 0};
    rFor (v, n, 2) {
        int u = fa[v];
        f[u][0] += min(f[v][0], f[v][1] + k);
        f[u][1] += min(f[v][0], f[v][1]);
    }
}

inline void solve(int l, int r, int ql, int qr) {
    if (l > r) return;
    int m = (l + r) >> 1; calc(m);
    auto [x, c] = min(f[1][0], f[1][1] + m); ans[m] = x;
    if (c == ql) For (i, l, m - 1) ans[i] = x + (i - m) * c;
    else solve(l, m - 1, ql, c);
    if (c == qr) For (i, m + 1, r) ans[i] = x + (i - m) * c;
    else solve(m + 1, r, c, qr);
}

int main() {
    io >> n;
    scanf("%s", a + 1);
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    solve(1, n, n, 1);
    For (i, 1, n) printf("%d\n", ans[i]);

    return 0;
}
