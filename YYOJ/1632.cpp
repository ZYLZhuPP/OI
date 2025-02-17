#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned int uint;
const int N = 17, N_ = 1 << N | 5;

int fa[N], g[N][N], f[N][N_];
int n, STA, x, aim;

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
    inline bool operator ~() {return ~c;}
} io;

int main() {
    io >> n; STA = 1 << n;
    For (i, 2, n) io >> fa[i];
    For (i, 1, n) io >> x, aim += (1 << (i - 1)) * x;

    For (i, 1, n) {
        for (int j = 1, f = i; j <= n; ++j, f = fa[f])
            if (f) g[i][j] = g[i][j - 1] ^ (1 << (f - 1));
            else g[i][j] = g[i][j - 1];
    }

    f[0][0] = 1;
    For (i, 0, n) {
        if (f[i][aim]) {
            printf("%d", i);
            return 0;
        }

        For (s, 0, STA - 1) if (f[i][s]) {
            f[i + 1][s] = 1;
            For (j, 1, n) f[i + 1][s ^ g[j][i + 1]] = 1;
        }
    }

    return 0;
} 
