#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5, Mo = 998244353;
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

int n, p, _[N], __[N], c[N], d[N][N], f[N];

int main() {
    io >> n;
    int a, b;
    io >> a >> b; p = ml(a, qPow(b, Mo - 2));
    _[0] = 1; For (i, 1, n) _[i] = ml(_[i - 1], p);
    __[0] = 1; For (i, 1, n) __[i] = ml(__[i - 1], Mo + 1 - p);
    For (i, 0, n) d[i][0] = c[i] = 1;
    For (i, 1, n) For (j, 1, i) d[i][j] = mo(ml(__[j], d[i - 1][j]) + ml(_[i - j], d[i - 1][j - 1]));
    For (i, 1, n) For (j, 1, i - 1) add(c[i], -ml(c[j], d[i][j]));
    For (i, 1, n) {
        int res = 0;
        For (j, 1, i - 1) add(res, ml(ml(c[j], d[i][j]), mo(mo(j * (i - j) + j * (j - 1) / 2) + mo(f[j] + f[i - j]))));
        add(res, ml(ml(c[i], d[i][i]), i * (i - 1) / 2));
        f[i] = ml(res, qPow(Mo + 1 - ml(c[i], d[i][i]), Mo - 2));
    }
    printf("%d", f[n]);

    return 0;
}
