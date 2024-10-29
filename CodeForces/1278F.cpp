#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, m, K, _[N], S[N][N], ans;

inline void init() {
    S[0][0] = 1;
    For (i, 1, N - 1) For (j, 1, i) S[i][j] = mo(S[i - 1][j - 1] + ml(j, S[i - 1][j]));
    _[0] = 1;
    For (i, 1, K) _[i] = ml(_[i - 1], n - i + 1);
}

int main() {
    io >> n >> m >> K;
    init();
    int x = qPow(m, Mo - 2), y = 1;
    For (i, 0, K) add(ans, ml(S[K][i], ml(_[i], y))), mul(y, x);
    printf("%d", ans);

    return 0;
}
