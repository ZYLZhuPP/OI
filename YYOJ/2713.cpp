#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, f[N][2], sz[N];
vector<int > es[N];

void dfs(int u) {
    sz[u] = 1;
    if (es[u].empty()) return f[u][0] = 2, void();
    int sum = 0, mx = 0, mn = 1e9, mn2 = 1e9;
    for (auto &v : es[u]) {
        dfs(v); sum += f[v][0], cmax(mx, sz[v]), sz[u] += sz[v];
        int x = f[v][1] - f[v][0];
        if (x <= mn) mn2 = mn, mn = x;
        else cmin(mn2, x);
    }
    f[u][0] = sum + 2 * sz[u] + min(mn + mn2, -2 * mx), f[u][1] = sum + mn;
}

int main() {
    io >> n;
    int x;
    For (i, 2, n) io >> x, es[x].pb(i);
    dfs(1);
    printf("%d", f[1][0]);

    return 0;
}