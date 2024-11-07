#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e3 + 5;
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

struct Node {
    int w; ll v;
    bool operator < (const Node &a) const { return w > a.w; }
} a[N];

int n, W, K;
ll f[N], g[N][N << 1], ans;

int main() {
    io >> n >> W >> K;
    For (i, 1, n) io >> a[i].w >> a[i].v;
    sort(a + 1, a + n + 1);
    rFor (i, n, 1) {
        For (j, 0, W) g[i][j] = g[i + 1][j];
        For (j, 0, W - a[i].w) cmax(g[i][j + a[i].w], g[i + 1][j] + a[i].v);
    }
    For (j, 0, W) cmax(ans, g[1][j]);
    For (i, 1, n) {
        rFor (j, K - 1, 0) cmax(f[j + 1], f[j] + a[i].v);
        cmax(ans, f[K] + g[i + 1][W]);
    }
    printf("%lld", ans);

    return 0;
}
