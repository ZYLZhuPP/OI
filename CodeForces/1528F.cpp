#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, m, K, P, dw[N], ivf[N], inv[N], ans, mip[N], pri[N / 10], psz, id[N];

inline void init() {
    dw[0] = 1; For (i, 1, K) dw[i] = ml(dw[i - 1], n - i + 1);
    int x = 1; For (i, 1, K) mul(x, i);
    ivf[K] = qPow(x, Mo - 2); rFor (i, K - 1, 0) ivf[i] = ml(ivf[i + 1], i + 1);
    inv[1] = 1; For (i, 2, K) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    id[1] = 1;
    For (i, 2, K) {
        if (!mip[i]) pri[mip[i] = ++psz] = i, id[i] = qPow(i, K);
        For (j, 1, mip[i]) {
            if (pri[j] > K / i) break;
            int x = i * pri[j];
            mip[x] = j, id[x] = ml(id[i], id[pri[j]]);
        }
    }
}

int main() {
    io >> n >> K; P = qPow(mo(-(n + 1)), Mo - 2);
    init();
    int x = min(n, K), y = 1, z = 1, a = qPow(P, K - x), b = qPow(n + 1, n - x);
    rFor (i, x, 0) {
        if (i < x) {
            mul(a, P); mul(b, n + 1);
            mul(y, ml(n - i - 1, inv[K - i]));
            z = mo(ml(z, mo(P + 1)) + ml(y, a));
        }
        add(ans, ml(ml(id[i], ml(dw[i], ivf[i])), ml(b, z)));
    }
    printf("%d", ans);

    return 0;
}