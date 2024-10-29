#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e6 + 5, M = 1e7 + 5, Mo = 1e9 + 7;
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

int T, n, m, ans, _2[M], fac[N], ivf[N];

inline void init() {
    _2[0] = 1;
    For (i, 1, M - 1) _2[i] = mo(_2[i - 1] << 1);
    fac[0] = 1;
    For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i);
    ivf[N - 1] = qPow(fac[N - 1], Mo - 2);
    rFor (i, N - 2, 0) ivf[i] = ml(ivf[i + 1], i + 1);
}

inline int C(int n, int m) { return n>=m? ml(fac[n], ml(ivf[n - m], ivf[m])): 0; }

int main() {
    init();
    io >> T;
    while (T--) {
        ans = 0;
        io >> n >> m;
        For (i, 0, n) {
            int x = n + m - i - 1;
            add(ans, ml(ml(C(n, i), C(m, i)), mo(ml(i + 2, _2[x]) + (x? ml(x, _2[x - 1]): 0))));
        }
        printf("%d\n", ans);
    }

    return 0;
}
