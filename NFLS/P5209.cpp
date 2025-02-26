#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

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

int n, m, b[N], a[N][N], c[N];

inline void solve(int n) {
    if (n == m) return;
    For (i, 1, m) {
        a[i][m + 1] = m + i;
        For (j, m + 2, n) a[i][j] = a[i][j - 1]==n? m + 1: a[i][j - 1] + 1;
    }
    For (i, m + 1, n) For (j, 1, m) a[i][j] = a[j][i];
    int o = n - 2 * m;
    For (i, 1, o) For (j, 1, i) a[m + j][m + i - j + 1] = 2 * m + i;
    For (i, 1, o) For (j, 1, i) a[n - j + 1][n - i + j] = n - i;
    For (i, m + 1, n) For (j, m + 1, n) if (a[i][j] == n) a[i + 1][j + 1] = m + 1; else if (a[i][j] && a[i][j] < 2 * m) a[i + 1][j + 1] = a[i][j] + 1;
    int x = 1;
    For (i, m + 1, n) rFor (j, n, m + 1) if (!a[i][j]) {
        if (!c[i - j + n]) c[i - j + n] = x, x = x==m? 1: x + 1;
        a[i][j] = c[i - j + n];
    }
    For (i, 1, 2 * n) c[i] = 0;
    m = n;
}

int main() {
    freopen("num.in", "r", stdin);
    freopen("num.out", "w", stdout);
    io >> n;
    For (i, 1, n) io >> b[i];
    For (i, 2, n) if (b[i] < 2 * b[i - 1]) return puts("No"), 0;
    m = a[1][1] = 1;
    For (i, 1, n) solve(b[i]);
    puts("Yes");
    For (i, 1, m) For (j, 1, m) printf("%d%c", a[i][j], " \n"[j==m]);

    fclose(stdin); fclose(stdout);
    return 0;
}
