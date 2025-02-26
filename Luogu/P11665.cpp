#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e6 + 5, S = 1 << 21;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, m, a[N], f[S], ans;

int main() {
    m = 21;
    io >> n; ans = n;
    For (i, 1, n) io >> a[i], a[i]--;
    For (i, 0, S - 1) {
        while (f[i] < n - 1 && (i >> a[f[i] + 1] & 1 || i >> a[f[i] + 2] & 1)) f[i]++;
        if (f[i] >= n - 1) cmin(ans, __builtin_popcount(i));
        For (j, 0, m - 1) if (~i >> j & 1) {
            int k = i | (1 << j);
            cmax(f[k], f[i]);
            if (j && i >> (j - 1) & 1) cmax(f[k ^ (1 << (j - 1))], f[i]);
        }
    }
    printf("%d", ans);

    return 0;
}
