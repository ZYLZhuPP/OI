#include<bits/stdc++.h>
using namespace std;

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

int T, n, a[N];
ll s[N], f[N], g[N], h[N];

int main() {
    io >> T;
    while (T--) {
        memset(h, 224, sizeof h);
        io >> n;
        For (i, 1, n) io >> a[i], s[i] = s[i - 1] + (a[i]==a[i - 1]? a[i]: 0);
        f[0] = 0;
        For (i, 1, n) {
            g[i] = max(f[i - 1], h[a[i]] + s[i - 1] + a[i]);
            f[i] = max(f[i - 1] + (a[i]==a[i - 1]? a[i]: 0), g[i]);
            cmax(h[a[i - 1]], g[i] - s[i]);
        }
        printf("%lld\n", f[n]);
    }

    return 0;
}
