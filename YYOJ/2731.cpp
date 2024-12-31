#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 1e9 + 7;
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

int n, x, y, inv[N], f[2][N][N], s[2][N], ans;

int main() {
    io >> n >> x; y = n - x;
    inv[1] = 1; For (i, 2, n) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    For (i, 0, x) For (j, 0, y) {
        f[0][i][j] = ml(s[0][i] + s[1][j], inv[i + j]);
        f[1][i][j] = ml(mo(s[0][i] + s[1][j]) + i, inv[i + j]);
        add(s[0][i], f[1][i][j]);
        add(s[1][j], f[0][i][j]);
    }
    ans = f[0][x][y];
    For (i, 1, n) mul(ans, i);
    printf("%d", ans);

    return 0;
}
