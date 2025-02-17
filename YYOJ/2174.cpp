#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
const int N = 1e3 + 5, Mo = 998244353;
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

int n, m, A, ans, C[N][N], p[N][N];

inline void init() {
    For (i, 0, N - 1) {
        C[i][0] = 1;
        For (j, 1, i) C[i][j] = mo(C[i - 1][j - 1] + C[i - 1][j]);
    } 
    For (i, 0, N - 1) {
        p[i][0] = 1;
        For (j, 1, N - 1) p[i][j] = ml(p[i][j - 1], i);
    }
}

inline int F(int i, int j, int k) {
    int r = 0;
    For (t, 0, j) if (t * k <= i) add(r, (t&1? -1: 1) * ml(C[j][t], C[i - t * k][j])); else break;
    return r;
}

int main() {
    init();
    io >> n >> m >> A;
    For (k, 1, A) For (i, 1, n) if (i * k <= m) {
        For (j, 0, n - i) {
            int x = 0;
            For (t, i, n - j) add(x, ml(C[n - j][t], p[A - k][n - j - t]));
            add(ans, ml(C[n][j], ml(x, F(m - i * k, j, k - 1))));
        }
    } else break;
    printf("%d", ml(ans, qPow(qPow(A, n), Mo - 2)));

    return 0;
}
