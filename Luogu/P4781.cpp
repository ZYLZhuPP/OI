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

int n, x[N], y[N], X;

inline int Lagrange(int n, int x[], int y[], int X) {
    int res = 0;
    For (i, 1, n) {
        int a = 1, b = 1;
        For (j, 1, n) if (i ^ j) mul(a, X - x[j]), mul(b, x[i] - x[j]);
        res = (res + 1ll * y[i] * a % Mo * qPow(b, Mo - 2)) % Mo;
    }
    return mo(res);
}

int main() {
    io >> n >> X;
    For (i, 1, n) io >> x[i] >> y[i];
    printf("%d", Lagrange(n, x, y, X));

    return 0;
}
