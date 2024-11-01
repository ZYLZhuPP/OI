#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 998244353;
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

int n, ans, fac[N], ivf[N], E[N][N];

inline void init() {
    fac[0] = 1;
    For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i);
    ivf[N - 1] = qPow(fac[N - 1], Mo - 2);
    rFor (i, N - 2, 0) ivf[i] = ml(ivf[i + 1], i + 1);
    For (i, 0, N - 1) E[i][0] = 1;
    For (i, 1, N - 1) For (j, 1, i) E[i][j] = mo(ml(j + 1, E[i - 1][j]) + ml(i - j, E[i - 1][j - 1]));
}

int main() {
    init();
    io >> n;
    For (i, 1, n) {
        ans = 0;
        For (j, i, n) add(ans, ml(E[j][i - 1], ml(fac[n], ivf[j])));
        printf("%d ", ans);
    }

    return 0;
}
