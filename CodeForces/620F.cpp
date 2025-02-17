#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

int n, m, a[N], l[N], r[N], s[N], f[N], ans[N];

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    For (i, 1, m) io >> l[i] >> r[i];
    For (i, 1, N - 1) s[i] = s[i - 1] ^ i;
    For (i, 1, n) {
        f[i] = a[i];
        For (j, i + 1, n) f[j] = max(f[j - 1], s[min(a[i], a[j]) - 1] ^ s[max(a[i], a[j])]);
        For (j, 1, m) if (l[j] <= i && i <= r[j]) cmax(ans[j], f[r[j]]);
    }
    For (i, 1, m) printf("%d\n", ans[i]);

    return 0;
}
