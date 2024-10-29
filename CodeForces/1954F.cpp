#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e3 + 5, Mo = 1e9 + 7;
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

int n, C, K, c[N][N], f[N][N], s[N][N], S[N][N], ans, cnt[N];

inline void init() {
    For (i, 0, N - 1) c[i][0] = 1;
    For (i, 1, N - 1) For (j, 1, i) c[i][j] = mo(c[i - 1][j - 1] + c[i - 1][j]);
}

int main() {
    init();
    io >> n >> C >> K;
    f[0][0] = 1; For (i, 0, n) s[i][0] = S[i][0] = 1;
    For (i, 1, n) For (j, 1, n) f[i][j] = s[i - 1][j - 1] - (i>C? s[i - C - 1][j - 1]: 0), s[i][j] = mo(s[i - 1][j] + f[i][j]);
    For (i, 1, n) For (j, 1, n) S[i][j] = mo(S[i][j - 1] + (i>=j? f[i][i - j]: 0));
    For (i, 1, n) cnt[__gcd(i, n)]++;
    For (i, 1, n) if (cnt[i]) {
        if (i <= C) { if (C + K == n) add(ans, cnt[i]); }
        else {
            int m = min(i, (C + K) / (n / i)), res = 0;
            For (j, 0, m) add(res, c[i][j]);
            For (j, 0, min(m, C - 1)) add(res, -ml(j + 1, S[i - j - 1][m - j]));
            add(ans, ml(res, cnt[i]));
        }
    }
    printf("%d", ml(ans, qPow(n, Mo - 2)));

    return 0;
}
