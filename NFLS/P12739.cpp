#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e7 + 20, M = 400;
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

int n, m, K, inv[N], fac[N], ivf[N];

struct mat {
    int o[M][M];
    mat(const int &x = 0) {
        memset(o, 0, sizeof o);
        For (i, 1, K) o[i][i] = x;
    }
    inline mat& operator *= (const mat &a) {
        mat r;
        For (i, 1, K) For (j, 1, K) {
            unsigned long long s = 0;
            For (k, 1, K) s += 1ull * o[i][k] * a.o[k][j];
            r.o[i][j] = s % Mo;
        }
        swap(*this, r);
        return *this;
    }
};

inline int cal1(int n) {
    mat A, B(1);
    A.o[1][1] = m, A.o[K][1] = 1 - m + Mo;
    For (i, 1, K - 1) A.o[i][i + 1] = 1;
    for (; n; n >>= 1, A *= A) if (n & 1) B *= A;
    return mo(B.o[1][1] - B.o[1][2]);
}

inline void init() {
    inv[1] = 1; For (i, 2, Mo - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1; For (i, 1, Mo - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
}

inline int C(int n, int m) { return ml(fac[n], ml(ivf[m], ivf[n - m])); }
inline int Lucas(int n, int m) { return n|m? n%Mo<m%Mo? 0: ml(C(n % Mo, m % Mo), Lucas(n / Mo, m / Mo)): 1; }

inline int cal2(int n) {
    int res = 0, x = qPow(m, n), y = ml(1 - m + Mo, qPow(qPow(m, K), Mo - 2));
    For (i, 0, n / K) add(res, ml(Lucas(n - K * i + i, i), x)), mul(x, y);
    return res;
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    io >> n >> m >> K >> Mo;
    if (K == 1) return printf("%d", qPow(m, n)), 0;
    if (2ll * K - 1 > n) return puts("0"), 0;
    if (m == 1) return puts("1"), 0;
    K = 2 * K - 1;
    printf("%d", mo(qPow(m, n) - ml(K<M? cal1(n): (init(), mo(cal2(n) - cal2(n - 1))), ml(m, qPow(m - 1, Mo - 2)))));
    
    fclose(stdin); fclose(stdout);
    return 0;
}