#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e18;
const int N = 8e3 + 5;
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

int n, a[N];
ll s[N], b[N], ans;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) {
        ans = INF;
        For (j, 1, n) s[j] = s[j - 1] + a[j];
        For (j, 3, n - 1) b[j] = b[j - 2] + a[j - 1] - a[j];
        set<ll > se;
        for (int j = n - 1; j >= 1; j -= 2) {
            se.insert(s[n] - s[j] + b[j]);
            ll x = s[j] + b[j];
            auto p = se.upper_bound(x); if (p == se.end()) p = prev(p);
            auto q = p==se.begin()? p: prev(p);
            cmin(ans, min(abs(*p - x), abs(*q - x)));
        }
        se.clear();
        for (int j = n - 2; j >= 1; j -= 2) {
            se.insert(s[n] - s[j] + b[j]);
            ll x = s[j] + b[j];
            auto p = se.upper_bound(x); if (p == se.end()) p = prev(p);
            auto q = p==se.begin()? p: prev(p);
            cmin(ans, min(abs(*p - x), abs(*q - x)));
        }
        printf("%lld\n", ans);
        a[n + 1] = a[1]; For (j, 1, n) a[j] = a[j + 1];
    }

    return 0;
}
