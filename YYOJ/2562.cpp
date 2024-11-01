#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 998244353;
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

int n, q, l = 1, r = 0, m = 1, f[N][41][41], g[N][21][41], ans;
char mp[N][21];

int main() {
    io >> n >> q;
    while (q--) {
        char op[5];
        scanf("%s", op);
        if (op[0] == 'A') {
            scanf("%s", mp[++r] + 1);
            if (l == r) {
                m = r;
                For (i, 1, n) if (mp[m][i] == '.') g[m][i][n + i] = 1;
                For (i, 1, 2 * n) f[m][i][i] = 1;
            } else {
                For (i, 1, 2 * n) For (j, 1, n) f[r][i][j] = f[r - 1][i][n + j];
                For (i, 1, 2 * n) For (j, 1, n) if (mp[r][j] == '.') {
                    if (j > 1) add(f[r][i][j + n], f[r - 1][i][j - 1]);
                    if (j < n) add(f[r][i][j + n], f[r - 1][i][j + 1]);
                    if (j > 2) add(f[r][i][j + n], f[r - 1][i][j - 2 + n]);
                    if (j + 2 <= n) add(f[r][i][j + n], f[r - 1][i][j + 2 + n]);
                }
            }
        } else if (op[0] == 'D') {
            if (l == m) {
                l++; m = r;
                if (l > r) continue;
                For (i, 1, n) if (mp[m][i] == '.') g[m][i][n + i] = 1;
                memset(f[m], 0, sizeof f[m]);
                For (i, 1, 2 * n) f[m][i][i] = 1;
                if (l < m) {
                    For (i, 1, n) if (mp[m - 1][i] == '.') {
                        g[m - 1][i][i] = 1;
                        if (i > 2) add(g[m - 1][i][i - 2 + n], g[m][i - 2][i - 2 + n]);
                        if (i + 2 <= n) add(g[m - 1][i][i + 2 + n], g[m][i + 2][i + 2 + n]);
                    }
                }
                rFor (i, m - 2, l) For (j, 1, n) if (mp[i][j] == '.') {
                    For (k, 1, 2 * n) {
                        if (j > 1) add(g[i][j][k], g[i + 2][j - 1][k]);
                        if (j < n) add(g[i][j][k], g[i + 2][j + 1][k]);
                        if (j > 2) add(g[i][j][k], g[i + 1][j - 2][k]);
                        if (j + 2 <= n) add(g[i][j][k], g[i + 1][j + 2][k]);
                    }
                }
            } else l++;
        } else {
            int x, y;
            io >> x >> y;
            if (l > r) { puts("0"); continue; }
            ans = 0;
            For (i, 1, 2 * n) add(ans, ml(g[l][x][i], f[r][i][y + n]));
            printf("%d\n", ans);
        }
    }

    return 0;
}
