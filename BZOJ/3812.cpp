#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1 << 15, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, m, S, out[N], in[N], _2[N], cnt[N], h[N], f[N], g[N], w[N];

int main() {
    io >> n >> m; S = 1 << n;
    int u, v;
    For (i, 1, m) io >> u >> v, u = 1 << (u - 1), v = 1 << (v - 1), out[u] |= v, in[v] |= u;
    _2[0] = 1; For (i, 1, m) _2[i] = mo(_2[i - 1] << 1);
    For (i, 1, S - 1) cnt[i] = cnt[i & (i - 1)] + 1;
    For (i, 1, S - 1) h[i] = h[i & (i - 1)] + cnt[in[i & -i] & i] + cnt[out[i & -i] & i];
    For (s, 1, S - 1) {
        int p = s & -s, ns = s ^ p;
        for (int t = ns; t; t = (t - 1) & ns) add(g[s], -ml(f[s ^ t], g[t]));
        f[s] = _2[h[s]];
        for (int t = s; t; t = (t - 1) & s) {
            int x = s ^ t, p = x & -x;
            w[t] = x? w[t ^ p] - cnt[out[p] & x] + cnt[in[p] & t]: 0;
            add(f[s], -ml(g[t], _2[w[t] + h[x]]));
        }
        add(g[s], f[s]);
    }
    printf("%d", f[S - 1]);

    return 0;
}
