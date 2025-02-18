#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int f[60][8], ans;
ll X, Y, Z, l[8], r[8];

inline int F(int k, int s) {
    if (k < 0) return 1;
    if (~f[k][s]) return f[k][s];
    int x = s&1? X>>k&1: 1, y = s&2? Y>>k&1: 1, z = s&4? Z>>k&1: 1, res = 0;
    For (i, 0, x) For (j, 0, y) if ((i ^ j) <= z) add(res, F(k - 1, s & ((i==x) | ((j==y) << 1) | (((i^j)==z) << 2))));
    return f[k][s] = res;
}

inline int calc(ll x, ll y, ll z) {
    if (x < 0 || y < 0 || z < 0) return 0;
    memset(f, -1, sizeof f);
    X = x, Y = y, Z = z;
    return F(59, 7);
}

int main() {
    freopen("qgygd.in", "r", stdin);
    freopen("qgygd.out", "w", stdout);
    ans = 1;
    For (i, 1, 7) io >> l[i] >> r[i], mul(ans, (r[i] - l[i] + 1) % Mo);
    ll lx = max({l[1], l[2], l[3]}) - 1, rx = min({r[1], r[2], r[3]});
    ll ly = max({l[5], l[6], l[7]}) - 1, ry = min({r[5], r[6], r[7]});
    ll lz = l[4] - 1, rz = r[4];
    if (lx >= rx || ly >= ry || lz >= rz) return printf("%d", ans), 0;
    add(ans, -mo(mo(calc(rx, ry, rz) + calc(lx, ly, rz)) + mo(calc(lx, ry, lz) + calc(rx, ly, lz))));
    add(ans, mo(mo(calc(lx, ly, lz) + calc(lx, ry, rz)) + mo(calc(rx, ly, rz) + calc(rx, ry, lz))));
    printf("%d", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}
