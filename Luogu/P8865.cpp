#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, Mo = 998244353;
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

int T, id, ansC, ansF, n, m, C, F;
int g[N][N], f[N][N], s[N][N];
char a[N][N];

int main() {
    io >> T >> id;
    while (T--) {
        ansC = ansF = 0;
        memset(g, 0, sizeof g); memset(f, 0, sizeof f); memset(s, 0, sizeof s);
        io >> n >> m >> C >> F;
        For (i, 1, n) scanf("%s", a[i] + 1);
        For (i, 1, n) rFor (j, m, 1) if (!(a[i][j] & 1)) g[i][j] = g[i][j + 1] + 1;
        For (i, 1, n) For (j, 1, m) if (!(a[i][j] & 1)) {
            f[i][j] = mo(f[i - 1][j] + g[i][j + 1]); s[i][j] = s[i - 1][j];
            if (i > 1 && !(a[i - 1][j] & 1)) {
                int x = ml(g[i][j + 1], f[i - 2][j]);
                add(ansC, x);
                add(s[i][j], x);
            }
            add(ansF, s[i - 1][j]);
        }
        printf("%d %d\n", C * ansC, F * ansF);
    }

    return 0;
}
