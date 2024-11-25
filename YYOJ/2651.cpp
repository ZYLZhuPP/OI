#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 15;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, ans, a[N][N], b[N][N], c[N][N];

inline void solve() {
    int x = 0;
    For (i, 1, n) For (j, 1, i) x += a[i][j] ^ b[i][j];
    cmin(ans, x);
}

inline void rotate() {
    For (i, 1, n) For (j, 1, i) c[i][j] = a[n - j + 1][i - j + 1];
    For (i, 1, n) For (j, 1, i) a[i][j] = c[i][j];
}

int main() {
    io >> n; ans = n * n;
    For (i, 1, n) For (j, 1, i) io >> a[i][j];
    For (i, 1, n) For (j, 1, i) io >> b[i][j];
    solve(); rotate();
    solve(); rotate();
    solve(); rotate();
    For (i, 1, n) For (j, 1, i / 2) swap(a[i][j], a[i][i - j + 1]);
    solve(); rotate();
    solve(); rotate();
    solve(); rotate();
    printf("%d", ans);

    return 0;
}
