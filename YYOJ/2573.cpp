#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
typedef long long ll;
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

int n, a[N], q[N], T, g[N];
ll s[N], S, f[N];

inline ll Y(int i) { return f[i] + s[i] * s[i]; }
inline lf K(int i, int j) { return 0.5 * (Y(i) - Y(j)) / (s[i] - s[j]); }
inline ll F(int i, int j) { return f[j] + (s[i] - s[j]) * (s[i] - s[j]); }

inline int calc(ll x) {
    int h = 1, t = 0; q[++t] = 0;
    For (i, 1, n) {
        while (h < t && K(q[h], q[h + 1]) < s[i]) h++;
        f[i] = F(i, q[h]) + x; g[i] = g[q[h]] + 1;
        while (h < t && K(q[t], i) < K(q[t], q[t - 1])) t--;
        q[++t] = i;
    }
    return g[n];
}

int main() {
    io >> n >> T; T++;
    For (i, 1, n) io >> a[i], s[i] = s[i - 1] + a[i], S += s[i - 1] * a[i];
    ll l = 0, r = 4e18, res = 0;
    while (l <= r) {
        ll m = (l + r) >> 1;
        if (calc(m) <= T) r = m - 1, res = m;
        else l = m + 1;
    }
    calc(res);
    printf("%lld", S - (s[n] * s[n] - (f[n] - T * res)) / 2);

    return 0;
}
