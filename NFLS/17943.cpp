#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 305, M = 1 << 5;

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

int n, C, m, S, tot;
array<int, 2 > l[N];
lf f[N][M], ans;

int main() {
    io >> n >> C; m = n * C; S = 1 << (n - 1);
    For (i, 0, n - 1) io >> l[i][0], l[i][1] = i;
    sort(l, l + n);
    do {
        For (i, 0, m) For (s, 0, S - 1) f[i][s] = 0;
        f[l[n - 1][0] * n][0] = 1;
        For (i, 1, m - 1) if (i % n) {
            int x = i % n - 1;
            For (j, i, m) For (s, 0, S - 1) if (~s >> x & 1) f[min(m, max(j, i + l[x][0] * n))][s | (1 << x)] += f[j][s];
        }
        ans += f[m][S - 1], tot++;
    } while (next_permutation(l, l + n - 1));
    printf("%.13lf", ans / tot / pow(C, n - 1));

    return 0;
}