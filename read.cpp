#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 998244353, M = Mo - 1;
inline int qPow(int a, int b, int Mo) { int r = 1; for (; b; b >>= 1, a = 1ll * a * a % Mo) if (b & 1) r = 1ll * r * a % Mo; return r; }

struct IO {
    int c, f;
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

int n, m, _[N], vis[N], inv[N], h[N];

inline void init() {
    For (i, 2, m) if (!vis[i]) for (int j = i + i; j <= m; j += i) vis[j] = 1;
    For (i, 0, m) _[i] = qPow(i, n, M);
}

inline int get(int m) {
    if (h[m]) return h[m];
    ll res = 1;
    For (i, 2, m) if (!vis[i]) {
        ll d = i, s = 0;
        while (d <= m) s += _[m] - _[m - m / d], d *= i;
        res = res * qPow(i, (s % M + M) % M, Mo) % Mo;
    }
    return h[m] = res;
}

int main() {
    // freopen("num.in", "r", stdin);
    // freopen("num.out", "w", stdout);
    io >> n >> m;
    init();
    ll ans = 1;
    rFor (i, m, 1) {
        ll x = 1ll * get(m / i) * qPow(i, _[m / i], Mo) % Mo;
        for (int j = i + i; j <= m; j += i) x = x * inv[j] % Mo;
        inv[i] = qPow(x, Mo - 2, Mo);
        ans = ans * qPow(x, i, Mo) % Mo;
    }
    printf("%lld\n", ans);

    // fclose(stdin); fclose(stdout);
    return 0;
}