#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e6 + 5;

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

int n, k, m, a[N], f[N][2], l[25], r[25];

int main() {
    io >> k >> m;
    n = 1 << k;
    For (i, 1, n - 1) io >> a[i], a[i]--;
    rFor (i, n - 1, 1)
        f[i][a[i]] = f[i << 1][a[i]] + f[i << 1 | 1][a[i]] + 1,
        f[i][!a[i]] = min(f[i << 1][!a[i]], f[i << 1 | 1][!a[i]]);
    For (i, 1, k + 1) {
        l[i] = n, r[i] = 1;
        int x = k + 2 - i;
        For (j, 1 << (x - 1), (1 << x) - 1)
            l[i] = min(l[i], f[j][0] + 1),
            r[i] = max(r[i], n - f[j][1]);
    }
    int x, y;
    while (m--) io >> x >> y, puts(l[y] <= x && x <= r[y]? "Yes": "No");

    return 0;
}