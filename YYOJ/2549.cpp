#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, M = 1e3 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, ll b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

ll n;
int K, A, B, ans, fac[N], ivf[N], inv[N];

struct poly {
    int o[M];
    poly(int x = 0) { memset(o, 0, sizeof o); o[0] = x; }
    poly operator * (poly &a) const {
        poly r;
        For (i, 0, K - 1) For (j, 0, K - 1) if (i + j < K) add(r.o[i + j], ml(o[i], a.o[j]));
        else add(r.o[(i + j) % K], ml(A, ml(o[i], a.o[j])));
        return r;
    }
};

inline poly qPow(poly a, ll b) {
    poly r(1);
    while (b) {
        if (b & 1) r = r * a;
        a = a * a;
        b >>= 1;
    }
    return r;
}

inline void init() {
    inv[1] = 1;
    For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1;
    For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
}

inline int C(int n, int m) { return n>=m? ml(fac[n], ml(ivf[n - m], ivf[m])): 0; }

int main() {
    init();
    io >> n >> K >> A >> B;
    if (K == 1) ans = qPow(mo(1 + ml(A, B)), n);
    else if (K > 1e3) {
        B = qPow(B, K);
        int x = 1, y = 1;
        For (i, 0, n) add(ans, ml(ml(x, y), C(n * K, i * K))), mul(x, A), mul(y, B);
    } else {
        poly x; x.o[0] = 1; x.o[1] = B;
        ans = qPow(x, n * K).o[0];
    }
    printf("%d", ans);

    return 0;
}
