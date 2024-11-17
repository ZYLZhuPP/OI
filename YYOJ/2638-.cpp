#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 1e9 + 7;
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

int T, n, q, dep[N], a[N], b[N], w[N], ivf[N];
vector<int > es[N];

inline void dfs0(int u, int pre) {
    dep[u] = dep[pre] + 1;
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u);
}

inline void build() {
    For (i, 1, n) dep[i] = 0, es[i].resize(0);
    For (i, 1, n) {
        if (a[b[i]] > a[i]) dep[i] = -1;
        else if (a[b[i]] + w[b[i]] > a[i]) es[b[i]].pb(i);
    }
    For (i, 1, n) if (dep[i] == -1) dfs0(i, 0);
}

inline void init() {
    int x = 1; For (i, 1, N - 1) mul(x, i);
    ivf[N - 1] = qPow(x, Mo - 2); rFor (i, N - 2, 0) ivf[i] = ml(ivf[i + 1], i + 1);
}

int main() {
    init();
    io >> T;
    while (T--) {
        io >> n >> q;
        For (i, 1, n) io >> a[i] >> b[i] >> w[i];
        build();
        int op, x, v, u;
        while (q--) {
            io >> op;
            if (op == 1) io >> x >> v, a[x] = v, build();
            else if (op == 2) io >> x >> v, w[x] = v, build();
            else {
                io >> u;
                if (!dep[u]) printf("%d\n", a[u]);
                else printf("%d\n", mo(a[u] + ml(w[u], ivf[dep[u]])));
            }
        }
    }

    return 0;
}
