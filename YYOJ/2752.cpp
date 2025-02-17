#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }
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

int n, K, inv[N], ivf[N], a[N], mu[N], pri[N], psz, mip[N], ans;

inline int S2(int n, int K) {
    int s = 0; cmin(K, n);
    For (i, 1, K) add(s, ml(a[K - i], ml(qPow(i, n), ivf[i])));
    return s;
}

int main() {
    io >> n >> K;
    if (n == 1 || K == 1) return puts("1"), 0;
    inv[1] = 1; For (i, 2, n) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    ivf[0] = 1; For (i, 1, n) ivf[i] = ml(ivf[i - 1], inv[i]);
    mu[1] = 1;
    For (i, 2, n) {
        if (!mip[i]) mu[pri[mip[i] = ++psz] = i] = -1;
        For (j, 1, mip[i]) {
            if (pri[j] > n / i) break;
            int x = i * pri[j];
            mip[x] = j; mu[x] = mu[i] * -(j < mip[i]);
        }
    }
    a[0] = 1; For (i, 1, n) a[i] = mo(a[i - 1] + (i&1? -1: 1) * ivf[i]);
    For (i, 1, n) if (mu[i]) add(ans, ml(mu[i], S2((n + i - 1) / i, K)));
    For (i, 1, n) add(ans, -mu[i]);
    printf("%d", ans);

    return 0;
}
