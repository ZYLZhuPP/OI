#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 998244353, inv2 = 499122177;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r = 1; for (; b; mul(a, a), b >>= 1) if (b & 1) mul(r, a); return r; }

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

int n, m, _3[N], __3[N], fa[N], sz[N], w[N];

inline int find(int u) {
    if (fa[u] == u) return u;
    int f = find(fa[u]);
    if (fa[u] ^ f) mul(w[u], w[fa[u]]), fa[u] = f;
    return f;
}

int main() {
    io >> n >> m;
    _3[0] = 1; For (i, 1, n) _3[i] = ml(_3[i - 1], 3);
    __3[n] = qPow(_3[n], Mo - 2); rFor (i, n - 1, 0) __3[i] = ml(__3[i + 1], 3);
    For (i, 1, n) fa[i] = i, sz[i] = w[i] = 1;
    while (m--) {
        int op, u, v;
        io >> op;
        if (op == 1) {
            io >> u >> v;
            mul(w[u], ml(2, _3[sz[v] - 1]));
            mul(w[v], qPow(w[u], Mo - 2));
            mul(w[v], _3[sz[u] - 1]);
            sz[u] += sz[v];
            fa[v] = u;
        } else {
            io >> u;
            find(u);
            int x = fa[u]^u? ml(w[u], w[fa[u]]): w[u];
            printf("%d\n", ml(x, _3[n - sz[fa[u]] + 1]));
        }
    }

    return 0;
}
