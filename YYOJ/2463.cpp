#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e4 + 5;
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

int T, n, m, ans, a[N], b[N], c[N], d[N], tot;

int main() {
    io >> T;
    while (T--) {
        tot = 0; ans = N;
        io >> n >> m;
        For (i, 1, n) {
            io >> a[i];
            int x = a[i]; d[i] = 0;
            b[++tot] = x;
            while (x > 1) x >>= 1, b[++tot] = x;
        }
        sort(b + 1, b + tot + 1);
        tot = unique(b + 1, b + tot + 1) - b - 1;
        rFor (i, tot, 1) {
            int x = b[i];
            For (j, 1, n) {
                while (a[j] / 2 >= x) a[j] >>= 1, d[j]++;
                c[j] = min(d[j] + abs(a[j] - x), min(d[j] + 1 + x - (a[j] / 2), N));
            }
            sort(c + 1, c + n + 1);
            int s = 0;
            For (j, 1, n - m) s += c[j];
            cmin(ans, s);
        }
        printf("%d\n", ans);
    }

    return 0;
}
