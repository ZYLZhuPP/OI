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

int n, m, fac[N], ivf[N], cnt[10], f[10][10][10][10], ans;

inline void dfs(int k, int s) {
    if (k > n) {
        f[cnt[1]][cnt[2]][cnt[3]][cnt[4]] = 1;
        return;
    }
    For (i, 1, m - 1) if (s + i != m) cnt[i]++, dfs(k + 1, (s + i) % m), cnt[i]--;
}

inline void init() {
    fac[0] = 1; For (i, 1, n) fac[i] = ml(fac[i - 1], i);
    ivf[n] = qPow(fac[n], Mo - 2); rFor (i, n - 1, 0) ivf[i] = ml(ivf[i + 1], i + 1);
}

int main() {
    io >> n >> m;
    init();
    if (n <= 5) {
        dfs(1, 0);
        For (i1, 0, n) For (i2, 0, n) For (i3, 0, n) For (i4, 0, n) if (f[i1][i2][i3][i4]) ans += fac[n] / fac[i1] / fac[i2] / fac[i3] / fac[i4];
    } else if (m == 3) {
        int x = (n - 1) / 2;
        ans = ml(ml(2, fac[n]), ml(ivf[n - x], ivf[x]));
    }
    printf("%d", ans);

    return 0;
}
