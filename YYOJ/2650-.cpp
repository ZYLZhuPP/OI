#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e3 + 5, M = 3e5 + 5;
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

int n, m, a[M];
ll f[N][N], ans;

mt19937 rnd(1145141);
inline void solve() {
    vector<pair<ll, int > > f[n + 5];
    For (i, 1, 5) f[2].pb({0, rnd() % n});
    For (len, 2, n) {
        sort(f[len].begin(), f[len].end(), greater<pair<ll, int > >());
        if (f[len].size() > 5) f[len].resize(5);
        for (auto &[x, l] : f[len]) {
            int r = l + len - 1;
            if (l) f[len + 1].pb({x + a[r] - a[l - 1], l - 1});
            if (r < n) f[len + 1].pb({x + a[r + 1] - a[l], l});
        }
    }
    for (auto &[x, l] : f[n + 1]) cmax(ans, x);
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    sort(a + 1, a + n + 1);
    a[0] = 0; a[++n] = m + 1;
    if (n <= 5001) {
        For (len, 3, n + 1) {
            For (l, 0, n - len + 1) {
                int r = l + len - 1;
                cmax(f[l][r], a[r] - a[l] + f[l + 1][r]);
                cmax(f[l][r], a[r] - a[l] + f[l][r - 1]);
            }
        }
        printf("%lld", f[0][n]);
    } else {
        For (o, 1, 10) solve();
        printf("%lld", ans);
    }

    return 0;
}
