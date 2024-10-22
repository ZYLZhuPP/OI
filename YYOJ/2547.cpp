#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }

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

int n, m, S, ans, f[N][N], g[N], h[N][N], a[N];

int main() {
    io >> n >> m >> S; ans = n;
    For (i, 1, n) io >> a[i];
    For (i, 2, n) {
        For (j, 1, i - 1) add(g[i], h[i][a[i] ^ a[j]] = f[i][j] = mo(1 + g[j] - h[j - 1][S ^ a[i] ^ a[j]]));
        add(ans, g[i]);
        For (j, 0, (1 << m) - 1) add(h[i][j], h[i - 1][j]);
    }
    printf("%d", ans);

    return 0;
}
