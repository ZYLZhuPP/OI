#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, inf = 1e9;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
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

int T, B, n, fa[N], l[N], r[N];
vector<int > es[N];

inline int dfs(int u, int mx, int mn) {
    int res = max({0, mx - r[u], l[u] - mn});
    cmax(mx, l[u]); cmin(mn, r[u]);
    for (auto &v : es[u]) cmax(res, dfs(v, mx, mn));
    return res;
}

int main() {
    io >> T >> B;
    while (T--) {
        int mx = 0, mn = inf;
        io >> n;
        For (i, 2, n) io >> fa[i], es[fa[i]].pb(i);
        For (i, 1, n) io >> l[i] >> r[i], cmax(mx, l[i]), cmin(mn, r[i]);
        printf("%d\n", max(dfs(1, 0, inf), (mx - mn + 1) / 2));
        if (B) {
            int x = (mx + mn) / 2;
            For (i, 1, n) printf("%d%c", min(r[i], max(l[i], x)), " \n"[i==n]);
        }
        For (i, 1, n) es[i].resize(0);
    }

    return 0;
}
