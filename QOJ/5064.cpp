#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int T, n, dep[N], sz[N];
vector<int > es[N];

inline void dfs0(int u, int pre) {
    dep[u] = dep[pre] + 1; sz[u] = 1;
    for (auto &v : es[u]) dfs0(v, u), sz[u] += sz[v];
}

int main() {
    io >> T;
    while (T--) {
        io >> n;
        int u, v;
        For (i, 1, n - 1) io >> u >> v, es[u].pb(v);
        dfs0(1, 0);
        For (i, 1, n) printf("%d %d\n", dep[i], n - sz[i] + 1), es[i].resize(0);
    }

    return 0;
}
