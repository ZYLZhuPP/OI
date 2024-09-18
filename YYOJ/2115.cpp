#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline int qPow(int a, int b) { int r=1; for(;b;b>>=1,a=ml(a,a)) if(b&1) r=ml(r,a); return r; }

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

int n, m, u, v, f[N], s[N], ans, inv[N];
vector<int > es[N];

namespace circle {
    int main() {
        inv[0] = inv[1] = 1;
        f[1] = s[1] = 1;
        For (i, 2, n) {
            inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
            f[i] = mo(2ll * s[i - 1] * inv[i] % Mo + 1ll * (i + 3) * inv[2] % Mo - inv[i]);
            s[i] = mo(s[i - 1] + f[i]);
        }
        ans = mo(f[n - 1] + n);
        printf("%d", ans);
        return 0;
    }
}

int main() {
    io >> n >> m;
    For (i, 1, m) {
        io >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
    }
    circle::main();

    return 0;
}
