#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e6 + 5;
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

int n, h, t, q[N], l;
ll E, T, f[N], s[N], d[N], mn = 1e18;

int main() {
    io >> n >> E >> T;
    For (i, 1, n) io >> s[i], d[i] = s[i] - s[i - 1];
    f[0] = 0;
    int h = 1, t = 0; q[++t] = 0;
    For (i, 1, n) {
        while (h <= t && 2 * (s[i] - s[q[h] + 1]) >= T) h++;
        while (2 * (s[i] - s[l + 1]) >= T) cmin(mn, f[l] - 2 * d[l + 1]), l++;
        f[i] = mn; if (h <= t) cmin(f[i], f[q[h]] + T - 2 * (s[i] - s[q[h]]));
        while (h <= t && f[i] + 2 * s[i] <= f[q[t]] + 2 * s[q[t]]) t--;
        q[++t] = i;
    }
    printf("%lld", E + 2 * s[n] + f[n]);

    return 0;
}
