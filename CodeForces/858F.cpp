#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

int n, m, dep[N];
vector<int > es[N];
vector<array<int, 3 > > ans;

inline int dfs(int u, int pre) {
    int x = 0;
    dep[u] = dep[pre] + 1;
    for (auto &v : es[u]) if (v ^ pre && dep[v] < dep[u]) {
        int y = !dep[v]? dfs(v, u): v;
        if (!y) continue;
        if (!x) x = y;
        else ans.pb({x, u, y}), x = 0;
    }
    if (x && pre) return ans.pb({x, u, pre}), 0;
    return u;
}

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (i, 1, n) if (!dep[i]) dfs(i, 0);
    printf("%d\n", (int)ans.size());
    for (auto &[x, y, z] : ans) printf("%d %d %d\n", x, y, z);

    return 0;
}
