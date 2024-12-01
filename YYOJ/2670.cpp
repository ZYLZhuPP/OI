#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 998244353;
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

int n, P, ans, f[N][N], s[N][N], fac[N], ivf[N];

inline void init() {
    fac[0] = 1; For (i, 1, n) fac[i] = ml(fac[i - 1], i);
    ivf[n] = qPow(fac[n], Mo - 2); rFor (i, n - 1, 0) ivf[i] = ml(ivf[i + 1], i + 1);
}

int main() {
    io >> n >> P;
    init();
    ans = qPow(P - 1, n);
    int x = 0, y = P - 1;
    For (i, 2, n) {
        int t = y;
        y = mo(ml(P - 2, y) + ml(P - 1, x));
        x = t;
    }
    add(ans, -x);
    For (i, 0, n) {
        For (j, i, n) {
            f[i][j] = i? mo(s[i - 1][j - 1] - (j>=P-1? s[i - 1][j - P + 1]: 0)): !j;
            s[i][j] = mo(s[i][j - 1] + f[i][j]);
            if (n - i >= j + P && (n - i - j) % P) add(ans, -ml(ml(P - 1, f[i][j]), ml(fac[n], ml(ivf[i], ivf[n - i]))));
        }
    }
    printf("%d", ans);

    return 0;
}
