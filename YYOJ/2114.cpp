#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, M = 2e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int n, m, k, u, v, ans;
int inv[M], fac[M], invfac[M];
vector<int > es[N];

void init() {
    inv[0] = inv[1] = 1;
    For (i, 2, M - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = invfac[0] = 1;
    For (i, 1, M - 1) fac[i] = ml(fac[i - 1], i), invfac[i] = ml(invfac[i - 1], inv[i]);
}
int C(int n, int m) {
    if (n < m) return 0;
    return ml(fac[n], ml(invfac[n - m], invfac[m]));
}

int main() {
    init();
    io >> n >> m >> k;
    For (i, 1, m) {
        io >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
    }
    if (k == 1) ans = m;
    else if (k == 2) For (i, 1, n) add(ans, 1ll * es[i].size() * (es[i].size() - 1) / 2 % Mo);
    else if (k == 3) {

    }

    printf("%d", ans);

    return 0;
}
