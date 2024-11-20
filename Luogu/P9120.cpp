#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
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

int T, K, ans, n, a[N][4], mx[4], mn[4];
mt19937 rnd(1145141);

int main() {
    io >> T >> K;
    while (T--) {
        ans = 1e9;
        io >> n;
        For (i, 0, K - 1) For (j, 1, n) io >> a[j][i];
        For (_, 1, 300) {
            shuffle(a + 1, a + n + 1, rnd);
            For (i, 0, K - 1) mx[i] = -1e9, mn[i] = 1e9;
            For (i, 1, n) {
                int res = 1e9, p = 0;
                For (k, 0, K - 1) {
                    int r = 0;
                    For (j, 0, K - 1) cmax(r, max(mx[j], a[i][(j + k) % K]) - min(mn[j], a[i][(j + k) % K]));
                    if (cmin(res, r)) p = k;
                }
                For (j, 0, K - 1) cmax(mx[j], a[i][(j + p) % K]), cmin(mn[j], a[i][(j + p) % K]);
                if (res >= ans) break;
            }
            int res = 0;
            For (j, 0, K - 1) cmax(res, mx[j] - mn[j]);
            cmin(ans, res);
        }
        printf("%d\n", ans);
    }

    return 0;
}
