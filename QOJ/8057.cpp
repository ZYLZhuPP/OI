#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;
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

int T, n;
ll ans, a[N], b[N], sa, sb;

int main() {
    int cnt = 0;
    io >> T;
    while (T--) {
        cnt++;
        ans = sa = sb = 0;
        io >> n;
        For (i, 0, n - 1) io >> a[i], sa += a[i];
        For (i, 0, n - 1) io >> b[i], sb += b[i];
        if (sa > sb) b[0] += sa - sb;
        else a[0] += sb - sa;
        int t = 0, mn = n, mx1 = -1, mx2 = -1, Mx = 0;
        rFor (i, n - 1, 0) if (b[i]) {
            while (t < n && !a[t]) t++;
            while (t < n - 1 - i) {
                cmax(mx2, t++);
                while (t < n && !a[t]) t++;
            }
            ll s = 0;
            while (t < n) {
                cmax(Mx, t + i);
                cmin(mn, t); cmax(mx1, t);
                if (s + a[t] >= b[i]) {
                    a[t] -= b[i] - s;
                    s = b[i];
                    break;
                }
                s += a[t]; a[t++] = 0;
                while (t < n && !a[t]) t++;
            }
            ans += s;
        }
        while (t < n && !a[t]) t++;
        if (t < n) cmax(mx2, t);
        if (!ans) puts("0");
        else if (Mx >= n || mx2 > mn) printf("%lld\n", ans);
        else if (mn < mx1) printf("%lld\n", ans - 1);
        else puts("0");
    }

    return 0;
}
