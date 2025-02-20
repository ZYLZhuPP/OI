#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 505;
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

int n;
ll A[N][N], B[N][N], f[N][N], ans = 1e18;

inline ll W(int k, int j, int i) {
    return B[j + 1][i] + A[n][j] - A[n][k] - A[i][j] + A[i][k];
}

int main() {
    io >> n;
    For (i, 1, n) For (j, 1, n) if (j ^ i) io >> A[i][j];
    For (j, 1, n) rFor (i, j, 1) B[i][j] = B[i + 1][j] + B[i][j - 1] - B[i + 1][j - 1] + A[i][j];
    For (i, 1, n) For (j, 1, n) A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
    For (i, 1, n - 1) {
        f[i][0] = W(0, 0, i);
        cmin(ans, f[i][0] + W(0, i, n));
        For (j, 1, i - 1) {
            f[i][j] = 1e18;
            For (k, 0, j - 1) cmin(f[i][j], f[j][k] + W(k, j, i));
            cmin(ans, f[i][j] + W(j, i, n));
        }
    }
    printf("%lld", ans);

    return 0;
}