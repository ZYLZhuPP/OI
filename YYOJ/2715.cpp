#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

int n, m;
set<int > g[N];
ll ans;

int main() {
    io >> n >> m; ans = -m;
    int u, v;
    For (i, 1, m) {
        io >> u >> v; if (u > v) swap(u, v);
        g[u].insert(v);
    }
    For (u, 1, n) if (!g[u].empty()) {
        ans += g[u].size();
        int v = *g[u].begin(); g[u].erase(v);
        if (g[u].size() > g[v].size()) swap(g[u], g[v]);
        for (auto &x : g[u]) g[v].insert(x);
    }
    printf("%lld", ans);

    return 0;
}
