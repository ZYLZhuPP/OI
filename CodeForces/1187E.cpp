#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 10;
typedef long long ll;

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

long long n, siz[N], dp[N], f[N], ans;
vector<int > T[N];

void dfs(int u, int pre) {
    siz[u] = 1;
    for (auto &v : T[u]) if (v ^ pre) {
        dfs(v, u);
        siz[u] += siz[v];
        dp[u] += dp[v];
    }
    dp[u] += siz[u];
}
void dfs2(int u, int pre) {
    for (auto &v : T[u]) if (v ^ pre) {
        f[v] = n + f[u] - 2 * siz[v];
        dfs2(v, u);
    }
}
int main() {
    io >> n;
    int u, v;
    for (int i = 1; i < n; i++) io >> u >> v, T[u].pb(v), T[v].pb(u);
    dfs(1, 0);
    f[1] = dp[1];
    dfs2(1, 0);
    For (i, 1, n) ans = max(ans, f[i]);
    printf("%lld", ans);
    return 0;
}