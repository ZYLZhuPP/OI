#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e6 + 5;
int Mo;
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

int T, n, fac[N], ivf[N];

inline int C(int n, int m) { return n>=m? ml(fac[n], ml(ivf[n - m], ivf[m])): 0; }

int main() {
    io >> T;
    while (T--) {
        io >> n >> Mo;
        if (n <= 2) { puts("0"); continue; }
        fac[0] = 1; For (i, 1, n) fac[i] = ml(fac[i - 1], i);
        ivf[n] = qPow(fac[n], Mo - 2); rFor (i, n - 1, 0) ivf[i] = ml(ivf[i + 1], i + 1);
        int s = 0, _ = 2;
        For (i, 0, n - 2) s = (1ll * s + ml(_, ml(C(n - 1, i), C(n - 1, i + 1)))) % Mo, mul(_, 2);
        printf("%d\n", mo(fac[n] - ml(s, qPow(n - 1, Mo - 2))));
    }

    return 0;
}
