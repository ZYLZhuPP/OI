#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
const int N = 1e4 + 5, inf = 1e9;
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

int n, a[N], b[N], f[N], g[N], q[N];

inline ll X(int i, int x) { return 1ll * i * b[x]; }
inline ll Y(int i, int x) { return g[i] - 1ll * i * a[x] + 1ll * i * (i + 1) / 2 * b[x]; }
inline lf K(int i, int j, int x) { return 1.0 * (Y(i, x) - Y(j, x)) / (X(i, x) - X(j, x)); }
inline ll F(int i, int j, int x) { return g[i] + 1ll * (j - i) * a[x] + 1ll * (j - i) * (j - i - 1) / 2 * b[x]; }

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) io >> b[i];
    memset(f, 31, sizeof f);
    f[0] = 0;
    For (i, 1, n) {
        For (j, 0, 10000) f[j] = g[j] = j<=5000? f[j << 1]: inf;
        int h = 1, t = 0; q[++t] = 0;
        For (j, 1, 10000) {
            while (h < t && K(q[h], q[h + 1], i) <= j) h++;
            ll x = F(q[h], j, i);
            if (x < inf) cmin(f[j], int(x));
            while (h < t && K(q[t], j, i) <= K(q[t], q[t - 1], i)) t--;
            q[++t] = j;
        }
    }
    printf("%d", f[1]);

    return 0;
}
