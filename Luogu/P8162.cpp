#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 505;
const lf INF = 1e10;
inline void cmin(lf &x, const lf &y) { y<x? x=y: 0; }

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

struct Node {
    int a, b;
    bool operator < (const Node &a) const { return (~b? b: 1e4) < (~a.b? a.b: 1e4); }
} a[N];

int n, K, B;
lf f[N][N], ans = INF;

inline lf solve(const int &o) {
    For (j, 0, o) For (k, 0, K - j) f[j][k] = INF;
    f[0][0] = 0;
    For (i, 1, n) rFor (j, min(i - 1, o), 0) rFor (k, min(K, i - 1) - j, 0) if (f[j][k] < INF) {
        cmin(f[j][k + 1], f[j][k] + (lf)a[i].a / (o + 1));
        if (~a[i].b) cmin(f[j + 1][k], f[j][k] + (lf)a[i].b / (j + 1));
    }
    return f[o][K - o];
}

int main() {
    io >> n >> K;
    For (i, 1, n) io >> a[i].a >> a[i].b, B += a[i].b != -1;
    sort(a + 1, a + n + 1);
    B = min(B, K - 1);
    //For (i, 0, B) printf("%d %.8lf\n", i, solve(i));
    int l = 0, r = B;
    while (l <= r) {
        if (l == r) { cmin(ans, solve(l)); break; }
        int m = (l + r) >> 1;
        lf L = solve(m), R = solve(m + 1);
        if (L < R) cmin(ans, L), r = m - 1;
        else cmin(ans, R), l = m + 1;
    }
    printf("%.8lf", ans);

    return 0;
}