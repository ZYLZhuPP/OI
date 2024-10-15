#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const ll INF = 1e18;
const int N = 2e5 + 5;
template<class C > inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    bool operator ~ () const { return ~c; }
} io;

int n, a[N];
ll f[N], g[N], ans = INF;

int main() {
    io >> n;
    For (i, 1, n - 1) io >> a[i];
    For (i, 0, 2e5) f[i] = i;
    For (i, 1, n - 1) {
        swap(f, g); memset(f, 31, sizeof f);
        ll mn = INF;
        For (j, a[i], 2e5) cmin(mn, g[j - a[i]] - (j - a[i])), cmin(f[j], j + mn);
        mn = INF;
        rFor (j, 2e5 - a[i], 0) cmin(mn, g[j + a[i]] + (j + a[i])), cmin(f[j], mn - j);
    }
    For (i, 0, 2e5) cmin(ans, (f[i] + i) >> 1);
    printf("%lld", ans);

    return 0;
}
