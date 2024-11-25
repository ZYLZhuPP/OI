#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
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

int T, n, m, a[N];
bool vis[N];
ll ans;

int main() {
    io >> T;
    while (T--) {
        ans = 1;
        memset(vis, 0, sizeof vis);
        io >> n >> m;
        int x;
        For (i, 1, n) io >> x, vis[x] = 1;
        n = 0;
        rFor (i, m, 1) if (vis[i]) a[++n] = i;
        For (i, 1, n) For (j, 2, n) {
            ll x = 1ll * a[i] * a[j];
            if (x < ans) break;
            int g = __gcd(a[i], a[j]);
            x = x / g / g;
            cmax(ans, x);
        }
        printf("%lld\n", ans);
    }

    return 0;
}
