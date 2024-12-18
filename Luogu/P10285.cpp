#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll inf = 1e18;
const int N = 1e5 + 5, M = 1 << 20;
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

int K, n, m, a[N], L, D;
ll f[M][20], g[20], ans = inf;

inline ll ceil(const ll &x, const ll &y) { return (x + y - 1) / y; }
inline ll T(const ll &d) { return min(ceil(K * (L - d), K + 1), K>1? ceil(K * d, K - 1): inf); }
inline ll solve(int i, ll t) {
    int d = (i * D + ceil(t, K)) % L;
    int k = lower_bound(a + 1, a + n + 1, d) - a;
    return K * (a[k] - d + ceil(t, K));
}

int main() {
    io >> L >> m >> n >> K; D = L / m;
    For (i, 1, n) io >> a[i];
    sort(a + 1, a + n + 1); a[++n] = a[1] + L;
    For (i, 0, m - 1) g[i] = T(i * D);
    memset(f, 31, sizeof f);
    f[1][0] = 0;
    For (s, 1, (1 << m) - 1) if (s & 1) {
        For (i, 0, m - 1) if (s >> i & 1) {
            if (i) f[s][i] = solve(i, f[s][i]);
            For (j, 0, m - 1) cmin(f[s | (1 << j)][j], f[s][i] + g[(j - i + m) % m]);
            if (s == (1 << m) - 1) cmin(ans, f[s][i]);
        }
    }
    printf("%lld", ans);

    return 0;
}
