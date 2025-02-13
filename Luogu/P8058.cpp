#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const __int128 O = 1;
const int N = 1e7 + 5;

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

int n, mip[N], pri[N], psz, mu[N];
ll K;

inline void init() {
    mu[1] = 1;
    For (i, 2, n) {
        if (!mip[i]) mu[pri[mip[i] = ++psz] = i] = -1;
        For (j, 1, mip[i]) {
            if (pri[j] > n / i) break;
            int x = i * pri[j];
            mip[x] = j; mu[x] = (j<mip[i]? -1: 0) * mu[i];
        }
        mu[i] += mu[i - 1];
    }
}

inline ll Euclid(ll a, ll b, ll c, int n) {
    if (n < 0) return 0;
    if (!a) return b / c * (n + 1);
    ll res = a / c * n * (n + 1) / 2 + b / c * (n + 1);
    a %= c, b %= c; int m = (O * a * n + b) / c;
    return res + 1ll * n * m - Euclid(c, c - b - 1, a, m - 1);
}

inline ll calc(ll a, ll b) {
    ll res = 0;
    for (int l = 1, r; l <= n; l = r + 1) r = n / (n / l), res += (mu[r] - mu[l - 1]) * Euclid(a, 0, b, n / l);
    return res;
}

int main() {
    io >> n >> K;
    init();
    ll a = 1, b = 2;
    For (_, 1, 60) {
        a <<= 1; b <<= 1;
        if (calc(a, b) >= K) a--;
        else a++;
    }
    a++;
    int x = 0, y = 1;
    For (i, 1, n) {
        int z = O * a * i / b;
        if (1ll * z * y > 1ll * x * i) x = z, y = i;
    }
    printf("%d %d", x, y);

    return 0;
}
