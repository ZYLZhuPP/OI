#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2005;
inline void cmin(int &x, const int &y) { y<x? x=y: 0; }

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
    inline bool operator ~ () { return ~c; }
} io;

int n, s[N], f[N][N];

int main() {
    io >> n;
    int x;
    For (i, 1, n) io >> x, s[i] = s[i - 1] + x;
    rFor (i, n - 1, 1) {
        int mn = s[n];
        For (j, 1, i) {
            if (i + 2 * j - 1 <= n) cmin(mn, f[i + 2 * j - 1][2 * j - 1]);
            if (i + 2 * j <= n) cmin(mn, f[i + 2 * j][2 * j]);
            f[i][j] = s[n] - s[i] - mn;
        }
    }
    printf("%d", s[n] - min(f[1][1], f[2][2]));

    return 0;
}