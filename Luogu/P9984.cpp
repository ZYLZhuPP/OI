#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 6e5 + 5, Mo = 1e9 + 7;
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

struct Node {
    int m, d;
    Node operator + (const Node &a) const { return {ml(m, a.m), mo(ml(d, a.m) + a.d)}; }
} f[N];

int n, m, fa[N];

inline void find(int x) {
    if (fa[x] == x) return;
    find(fa[x]);
    f[x] = f[x] + f[fa[x]];
    fa[x] = fa[fa[x]];
}

int main() {
    io >> n >> m;
    For (i, 1, n + m) fa[i] = i, f[i] = {1, 0};
    int u, v;
    For (i, 1, m) {
        io >> u >> v;
        find(u); find(v);
        if (fa[u] ^ fa[v]) {
            Node x = f[u], y = f[v], z = {10, i};
            f[fa[u]] = z + y; f[fa[v]] = z + x;
            fa[fa[u]] = fa[fa[v]] = n + i;
        }
    }
    For (i, 1, n) find(i), printf("%d\n", f[i].d);

    return 0;
}
