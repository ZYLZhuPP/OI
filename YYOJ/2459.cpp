#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i   )
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, m, a[N], p[N], dep[N], f[N][N], ans;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    dep[1] = 1;
    int j = 0;
    For (i, 2, n) {
        while (j && a[i] ^ a[j + 1]) j = p[j];
        if (a[i] == a[j + 1]) j++;
        p[i] = j; dep[i] = dep[j] + 1;
    }
    For (i, 1, m) {
        rFor (j, min(n, i - 1), 0) {
            cmax(f[i - 1][p[j]], f[i - 1][j]);
            if (j < n) cmax(f[i][j + 1], f[i - 1][j] + dep[j + 1]);
        }
    }
    For (i, 0, n) cmax(ans, f[m][i]);
    printf("%d", ans);

    return 0;
}
