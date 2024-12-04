#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll inf = 2e18;
const int N = 1e5 + 5;

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

int n, q, t[N];
vector<int > c[N], f[61][N];
vector<ll > g[61][N];

int main() {
    io >> n >> q;
    For (i, 1, n) {
        io >> t[i];
        c[i].resize(t[i]);
        For (j, 0, 60) f[j][i].resize(t[i]), g[j][i].resize(t[i]);
    }
    For (i, 1, n) For (j, 0, t[i] - 1) io >> c[i][j];
    for (int _ = 1; _ <= 1e5; _ <<= 1) {
        For (i, 1, n) if (t[i] == _) {
            For (k, 0, _ - 1) {
                int x = c[i][k]; ll d = 1;
                while (t[x] < _ && d < inf) {
                    int y = f[60][x][(k + d) & (t[x] - 1)];
                    d += g[60][x][(k + d) & (t[x] - 1)];
                    x = y;
                }
                f[0][i][k] = x; g[0][i][k] = min(inf, d);
            }
        }
        For (j, 1, 60) For (i, 1, n) if (t[i] == _) For (k, 0, _ - 1) {
            int x = f[j - 1][i][k]; ll d = g[j - 1][i][k];
            if (t[x] ^ _) {
                f[j][i][k] = x; g[j][i][k] = d;
                continue;
            }
            f[j][i][k] = f[j - 1][x][(k + d) & (_ - 1)];
            g[j][i][k] = min(inf, g[j - 1][x][(k + d) & (_ - 1)] + d);
        }
    }
    int x; ll T, d, w;
    while (q--) {
        io >> x >> T >> d;
        while (d) {
            rFor (j, 60, 0) if ((w = g[j][x][T & (t[x] - 1)]) <= d) {
                int _ = t[x];
                x = f[j][x][T & (_ - 1)];
                T += w; d -= w;
                if (t[x] > _) j = 61;
            }
            if (d) x = c[x][T & (t[x] - 1)], T++, d--;
        }
        printf("%d\n", x);
    }

    return 0;
}
