#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int M = 4e4, Mo = 1e9 + 7;
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

struct mat {
    int o[3][3];
    mat() { memset(o, 0, sizeof o); }
    mat operator * (const mat &a) const {
        mat r;
        For (k, 0, 2) For (i, 0, 2) For (j, 0, 2) add(r.o[i][j], ml(o[i][k], a.o[k][j]));
        return r;
    }
} g[M], f[M];

int T, n, ans;

int main() {
    f[0].o[0][0] = f[0].o[1][1] = f[0].o[2][2] = 1;
    f[1].o[0][0] = f[1].o[0][1] = f[1].o[1][2] = f[1].o[2][0] = 1;
    For (i, 2, M - 1) f[i] = f[i - 1] * f[1];
    g[0] = f[0]; g[1] = f[M - 1] * f[1]; For (i, 2, M - 1) g[i] = g[i - 1] * g[1];
    io >> T;
    while (T--) {
        io >> n; n--;
        mat x = g[n / M] * f[n % M];
        ans ^= mo(mo(x.o[0][0] << 1) + x.o[0][2] - 1);
    }
    printf("%d", ans);

    return 0;
}
