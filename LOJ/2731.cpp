#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e3 + 5, Mo = 1e9 + 7;
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

int n, a[N][4], f[N][N][2], m;
char s[4][N];

inline int A(int n, int m) { return !m? 1: m==1? n: n * (n - 1); }

int main() {
    io >> n;
    For (i, 1, 3) scanf("%s", s[i] + 1);
    For (j, 1, 3) For (i, 1, n) a[i][j] = s[j][i] == 'x';
    if (a[1][1] || a[1][3] || a[n][1] || a[n][3]) return puts("0"), 0;
    For (i, 2, n - 2) if ((a[i][1] && a[i + 1][1]) || (a[i][3] && a[i + 1][3])) return puts("0"), 0;
    f[0][0][0] = 1;
    For (i, 1, n) {
        int x = a[i][1] + a[i][3];
        if (a[i][2]) {
            For (j, 0, m) {
                add(f[i][j + x + 1][0], ml(mo(f[i - 1][m][0] + mo(f[i - 1][m][1] - f[i - 1][j][1])), A(j + x, x)));
                For (k, 0, x - 1) add(f[i][j + k + 1][1], ml((1 + min(k, x - k)) * f[i - 1][j][0], ml(A(j + k, k), A(m - j + x - k, x - k))));
            }
            m += x + 1;
        } else {
            f[i][0][0] = ml(mo(f[i - 1][m][0] + f[i - 1][m][1]), A(m + x, x));
            m += x;
        }
        For (j, 1, m) For (k, 0, 1) add(f[i][j][k], f[i][j - 1][k]);
    }
    printf("%d", f[n][m][0]);

    return 0;
}
