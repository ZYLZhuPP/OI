#include<bits/stdc++.h>
using namespace std;

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

int T, k, c[N][N], s[N][N], n, m;

int main() {
    io >> T >> k;
    For (i, 0, N - 1) c[i][0] = 1;
    For (i, 1, N - 1) For (j, 1, i) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % k;
    For (i, 1, N - 1) For (j, 1, N - 1) s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + (j <= i && !c[i][j]);
    while (T--) io >> n >> m, printf("%d\n", s[n][m]);
    
    return 0;
}
