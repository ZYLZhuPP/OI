#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, ll b) { int r = 1; for (; b; mul(a, a), b >>= 1) if (b & 1) mul(r, a); return r; }

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

int n, A, B, P, _[N], __[N], f[N], g[N], ans, fac[N], ivf[N];

int main() {
    io >> n;
    io >> A >> B; P = ml(A, qPow(B, Mo - 2));
    _[0] = 1; For (i, 1, n) _[i] = ml(_[i - 1], P);
    __[0] = 1; For (i, 1, n) __[i] = ml(__[i - 1], Mo + 1 - P);
    fac[0] = 1; For (i, 1, n) fac[i] = ml(fac[i - 1], i);
    ivf[n] = qPow(fac[n], Mo - 2); rFor (i, n - 1, 0) ivf[i] = ml(ivf[i + 1], i + 1);
    f[0] = 1; g[1] = 1;
    For (i, 1, n - 1) {
        if (i > 1) g[i] = mo(ml(g[i - 1], g[i - 1]) + 2);
        if (mo(P << 1) == 1) f[i] = ml(ml(fac[n], qPow(qPow(2, 1ll * i * (n - i)), Mo - 2)), ml(ivf[n - i], ivf[i]));
        else f[i] = ml(f[i - 1], ml(mo(_[n - i + 1] - __[n - i + 1]), qPow(mo(_[i] - __[i]), Mo - 2)));
        add(ans, ml(f[i], g[i]));
    }
    printf("%d", ans);

    return 0;
}
