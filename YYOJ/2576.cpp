#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, Mo = 998244353;
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

int n, a[N], pos, ans, f[N][N], C[N][N];

inline void init() {
    For (i, 0, N - 1) C[i][0] = 1;
    For (i, 1, N - 1) For (j, 1, i) C[i][j] = mo(C[i - 1][j - 1] + C[i - 1][j]);
}

int main() {
    init();
    io >> n;
    For (i, 1, n) {
        io >> a[i];
        if (a[i] == a[i - 1]) {
            if (pos) return puts("0"), 0;
            pos = i;
        }
    }
    if (pos) {
        ans = 2;
        For (i, pos, n - 1) a[i] = a[i + 1];
        a[n--] = 0;
    } else ans = 1;
    For (i, 1, n + 1) f[i][i - 1] = 1;
    For (len, 1, n) {
        For (l, 1, n - len + 1) {
            int r = l + len - 1;
            For (k, l, r) if (a[k] ^ a[l - 1] && a[k] ^ a[r + 1]) add(f[l][r], ml(C[r - l][k - l], ml(f[l][k - 1], f[k + 1][r])));
        }
    }
    printf("%d", ml(ans, f[1][n]));

    return 0;
}
