#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 1e9 + 7;
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

int n, mip[N], pri[N], psz, phi[N], ans;

inline void init() {
    For (i, 2, N - 1) {
        if (!mip[i]) pri[++psz] = i, mip[i] = psz, phi[i] = i - 1;
        For (j, 1, mip[i]) {
            int x = i * pri[j];
            if (x >= N) break;
            mip[x] = j; phi[x] = phi[i] * (pri[j] - (j!=mip[i]));
        }
    }
}

int main() {
    init();
    io >> n;
    For (d, 1, n) For (i, 2, n / d) {
        if (i * d >= n) break;
        int x = n - i * d, l = 1ll * x * d / __gcd(x, d);
        add(ans, ml(l, phi[i]));
    }
    printf("%d", ans);

    return 0;
}
