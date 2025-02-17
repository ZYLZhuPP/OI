#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

int n, co[N], cnt[N], sum, f[N], mx, son[N], sz[N];
vector<int > T[N];

void dfs0(int u, int pre) {
    sz[u] = 1;
    for (auto &v : T[u]) if (v ^ pre) {
        dfs0(v, u);
        if (sz[v] > sz[son[u]]) son[u] = v;
        sz[u] += sz[v];
    }
}

void add(int u, int d) {
    int c = co[u];
    cnt[c] += d;
    if (cnt[c] > mx) sum = c, mx = cnt[c];
    else if (cnt[c] == mx) sum += c;
}

void dfs(int u, int pre, int d) {
    add(u, d);
    for (auto &v : T[u]) if (v ^ pre) dfs(v, u, d);
}

void solve(int u, int pre) {
    for (auto &v : T[u]) if (v ^ pre && v ^ son[u]) solve(v, u);
    if (son[u]) solve(son[u], u);
    add(u, 1);
    for (auto &v : T[u]) if (v ^ pre && v ^ son[u]) dfs(v, u, 1);
    f[u] = sum;
    if (son[pre] ^ u) dfs(u, pre, -1), sum = mx = 0;
}

int main() {
    io >> n;
    For (i, 1, n) io >> co[i];
    int u, v;
    For (i, 1, n - 1) io >> u >> v, T[u].pb(v), T[v].pb(u);
    dfs0(1, 0);
    solve(1, 0);
    For (i, 1, n) printf("%d ", f[i]);

    return 0;
}
