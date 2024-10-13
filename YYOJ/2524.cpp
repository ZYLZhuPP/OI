#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 1e5 + 5;
template<class C > inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    bool operator ~ () const { return ~c; }
} io;

int T, lg2[N], mn[N][18], n, dep[N];
ll ans;
vector<int > f[N], es[N];

inline int query(int l, int r) {
    int k = lg2[r - l + 1];
    return min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

inline void dfs(int u, int pre) {
    dep[u] = dep[pre] + 1;
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
        int a = f[u].size(), b = f[v].size();
        if (b > a) swap(f[u], f[v]), swap(a, b);
        For (i, 0, b - 1) {
            int x = b - i, j = a - x;
            cmin(f[u][j] += f[v][i], query(x + 1, x + dep[u]));
        }
        f[v].resize(0);
    }
    f[u].pb(query(1, dep[u]));
}

int main() {
    lg2[1] = 0; For (i, 2, N - 1) lg2[i] = lg2[i >> 1] + 1;
    io >> T;
    while (T--) {
        ans = 0;
        io >> n;
        For (i, 1, n) io >> mn[i][0];
        For (j, 1, 17) For (i, 1, n - (1 << j) + 1) mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
        int u, v;
        For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
        dfs(1, 0);
        for (auto &x : f[1]) ans += x;
        printf("%lld\n", ans);
        f[1].resize(0); For (i, 1, n) es[i].resize(0);
    }

    return 0;
}
