#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
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

int T, n, X, Y, K, x[N], y[N];
ll s[N], l[N], r[N], ans;

inline void solve(int kx, int ky) {
    int S = kx * X + ky * Y;
    For (i, 1, n) s[i] = s[i - 1] + kx * x[i] + ky * y[i] + K;
    For (i, 1, n) {
        if (!s[n]) { if (s[i] < S) r[i] = -1; }
        else if (s[n] > 0) { if (s[i] < S) cmax(l[i], (S - s[i] - 1) / s[n] + 1); }
        else { cmin(r[i], s[i]<S? -1: (S - s[i]) / s[n]); }
    }
}

int main() {
    io >> T;
    while (T--) {
        ans = 4e18;
        io >> n >> K >> X >> Y;
        For (i, 1, n) io >> x[i] >> y[i], l[i] = 0, r[i] = 1e18;
        if (!X && !Y) { puts("0"); continue; }
        solve(1, 1); solve(1, -1); solve(-1, 1); solve(-1, -1);
        For (i, 1, n) if (l[i] <= r[i]) cmin(ans, i + l[i] * n);
        printf("%lld\n", ans<4e18? ans: -1);
    }

    return 0;
}
