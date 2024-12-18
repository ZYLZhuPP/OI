#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1 << 20;

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

int T, n, g[21][20], f[21][N];
char s[25], t[25];

inline int solve(int a, int b) {
    if (!a) return 0;
    For (i, 1, n) {
        For (j, 0, n - 1) if (b >> j & 1) a ^= 1 << ((i + j - 1) % n);
        if (f[i][a]) return i;
    }
    return -1;
}

int main() {
    io >> T >> n;
    For (i, 1, n) For (j, 0, n - 1) For (k, 0, i - 1) g[i][j] |= 1 << ((j + k) % n);
    f[0][0] = 1;
    For (i, 1, n) For (s, 0, (1 << n) - 1) if (f[i - 1][s]) For (j, 0, n - 1) f[i][s ^ g[i][j]] = 1;
    while (T--) {
        int a = 0, b = 0;
        scanf("%s%s", s, t);
        For (i, 0, n - 1) a |= (s[i] & 1) << i, b |= (t[i] & 1) << i;
        printf("%d\n", solve(a, b));
    }

    return 0;
}
