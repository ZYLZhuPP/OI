#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, ans, inv[N], fac[N], ivf[N];

inline void init() {
    inv[1] = 1;
    For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1;
    For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
}

inline int C(int n, int m) { return n>=m? ml(fac[n], ml(ivf[n - m], ivf[m])): 0; }

int main() {
    init();
    io >> n;
    ans = C(2 * n - 1, n);
    For (i, 1, n) {
        int x = i * (3 * i - 1) / 2, y = i * (3 * i + 1) / 2;
        if (x <= n) add(ans, (i&1? -1: 1) * C(2 * n - x - 1, n - 1)); else break;
        if (y <= n) add(ans, (i&1? -1: 1) * C(2 * n - y - 1, n - 1)); else break;
    }
    printf("%d", ans);

    return 0;
}
