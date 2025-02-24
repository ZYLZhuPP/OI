#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, K, q, g[6];
ll f[N];

inline void upd(int v, ll w) {
    rFor (i, n, v) cmax(f[i], f[i - v] + w);
}

inline void solve(int v, int w) {
    int k = min(K, n / v);
    for (int i = 1; i < k; k -= i, i <<= 1) upd(i * v, 1ll * i * w);
    upd(k * v, 1ll * k * w);
}

int main() {
    io >> K; K = 3 * (K - 1);
    n = 1e6;
    For (i, 0, 5) io >> g[i];
    For (i, 1, n) {
        int x = i, k = 0;
        while (x) {
            int y = x % 10;
            if (!(y % 3)) f[i] += 1ll * (y / 3) * g[k];
            x /= 10; k++;
        }
    }
    int x = 1;
    For (i, 0, 5) solve(3 * x, g[i]), x *= 10;
    io >> q;
    while (q--) io >> x, printf("%lld\n", f[x]);

    return 0;
}
