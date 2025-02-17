#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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

int n, fa[N], sz[N];
ll s[N];
array<int, 3 > es[N];

inline int find(int x) { return x^fa[x]? fa[x] = find(fa[x]): x; }

int main() {
    while (~(io >> n)) {
        For (i, 1, n) fa[i] = i, sz[i] = 1, s[i] = 0;
        int u, v, w;
        For (i, 1, n - 1) io >> u >> v >> w, es[i] = {w, u, v};
        sort(es + 1, es + n);
        rFor (i, n - 1, 1) {
            auto [w, u, v] = es[i];
            u = find(u); v = find(v);
            s[u] = max(s[u] + 1ll * w * sz[v], s[v] + 1ll * w * sz[u]);
            sz[u] += sz[v]; fa[v] = u;
        }
        printf("%lld\n", s[find(1)]);
    }

    return 0;
}
