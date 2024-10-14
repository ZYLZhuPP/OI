#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 6e3 + 5, Mo = 1211221111;
inline void add(int &x, const int &y) { x = (1ll * Mo + x + y) % Mo; }
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

int n, m, ans, C[N][N], fac[N], _2[N], __2[N];

inline void init() {
    For (i, 0, N - 1) C[i][0] = 1;
    For (i, 1, N - 1) For (j, 1, i) C[i][j] = (0ll + C[i - 1][j - 1] + C[i - 1][j]) % Mo;
    fac[0] = 1; For (i, 1, N - 1) fac[i] = ml(fac[i - 1], i);
    _2[0] = __2[0] = 1; For (i, 1, N - 1) _2[i] = ml(_2[i - 1], 2), __2[i] = ml(__2[i - 1], 605610556);
}

int main() {
    init();
    io >> n >> m;
    For (a, 0, n) if (m <= n + a && n + a <= 2 * m) {
        int b = n + a - m, x = 0;
        For (i, 0, a) add(x, (i&1? -1: 1) * ml(ml(C[a][i], C[b][i]), ml(ml(fac[i], _2[i]), fac[n + a - 2 * i])));
        add(ans, ml(ml(x, __2[a + b]), ml(C[n][a], C[m][b])));
    }
    printf("%d", ans);

    return 0;
}
