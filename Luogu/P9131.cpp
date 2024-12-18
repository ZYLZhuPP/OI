#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, M = 1 << 20, Mo = 1e9 + 7;
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

int n, m, S, fac[N], ivf[N], b[N], c[M], s[21][M];
char a[N];

inline void init() {
    fac[0] = 1; For (i, 1, n) fac[i] = ml(fac[i - 1], i);
    ivf[n] = qPow(fac[n], Mo - 2); rFor (i, n, 1) ivf[i - 1] = ml(ivf[i], i);
}

int main() {
    io >> n >> m; S = 1 << m;
    init();
    For (i, 0, m - 1) {
        scanf("%s", a + 1);
        For (j, 1, n) if (a[j] == 'H') b[j] |= 1 << i;
    }
    For (i, 1, n) c[b[i]]++;
    For (i, 0, S - 1) {
        int x = 1, y = 0;
        For (j, 0, m - 1) if (i >> j & 1) add(x, s[j][i ^ (1 << j)]);
        For (j, 1, c[i]) add(y, ml(fac[c[i]], ivf[c[i] - j]));
        s[0][i] = ml(x, y);
        For (j, 0, m - 1) s[j + 1][i] = mo(s[j][i] + (i>>j&1? s[j][i ^ (1 << j)]: 0));
    }
    printf("%d", s[m][S - 1]);

    return 0;
}
