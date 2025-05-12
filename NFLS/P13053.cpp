#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 6005;
int Mo;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, K, _[N], C[N][N], f[N], g[N], h[N], ans;

int main() {
    freopen("random.in", "r", stdin);
    freopen("random.out", "w", stdout);
    io >> n >> K >> Mo;
    _[0] = 1; For (i, 1, n) _[i] = 2ll * K * _[i - 1] % Mo;
    For (i, 0, n) C[i][0] = 1;
    For (i, 1, n) For (j, 1, i) C[i][j] = mo(C[i - 1][j] + C[i - 1][j - 1]);
    for (int i = 0; i <= n; i += 2) h[i] = C[i][i / 2];
    f[0] = g[0] = 1;
    for (int i = 2; i <= n; i += 2) {
        g[i] = ml(K, h[i]);
        for (int j = 2; j < i; j += 2) add(g[i], ml(ml(g[j], h[i - j]), mo(ml(K, C[i - 1][j]) - C[i - 1][j - 1])));
    }
    ans = ml(n + 1, _[n]);
    for (int i = 2; i <= n; i += 2) {
        f[i] = g[i];
        for (int j = 2; j < i; j += 2) add(f[i], -ml(f[j], g[i - j]));
        add(ans, -ml(n - i + 1, ml(f[i], _[n - i])));
    }
    printf("%d", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}
