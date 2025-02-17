#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1 << 20, Mo = 998244353;
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

int n, m, a[N], b[N], ans[N], Ans, inv[N];

int lim, R[N];
inline void NTT(int a[], int opt) {
    For (i, 0, lim - 1) if (i < R[i]) swap(a[i], a[R[i]]);
    for (int k = 1; k < lim; k <<= 1) {
        int m = k << 1, o = qPow(3, (Mo - 1) / m);
        for (int i = 0; i < lim; i += m)
            for (int j = i, p = 1; j < i + k; ++j, mul(p, o)) {
                int x = ml(a[j + k], p);
                a[j + k] = mo(a[j] - x);
                add(a[j], x);
            }
    }
    if (!~opt) {
        reverse(a + 1, a + lim);
        int x = qPow(lim, Mo - 2);
        For (i, 0, lim - 1) mul(a[i], x);
    }
}

int main() {
    inv[1] = 1; For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    if (m == 1) {
        int s = 0;
        For (i, 1, n) add(s, a[i]);
        printf("%d", ml(s, inv[2]));
    } else if (n == 2) printf("%d", ml(mo(qPow(mo(a[1] + a[2]), n + m) - qPow(a[1], n + m) - qPow(a[2], n + m) + Mo), qPow(ml(ml(a[1], a[2]), ml(n + m, n + m - 1)), Mo - 2)));
    else {
        lim = 1; while (lim <= m * 2) lim <<= 1;
        For (i, 0, lim - 1) R[i] = R[i >> 1] >> 1 | ((i & 1) * (lim >> 1));
        ans[0] = 1;
        For (i, 1, n) {
            b[0] = 1; For (j, 1, m) b[j] = ml(b[j - 1], ml(a[i], inv[j + 1]));
            NTT(ans, 1); NTT(b, 1);
            For (j, 0, lim - 1) mul(ans[j], b[j]);
            NTT(ans, -1);
            For (j, m + 1, lim - 1) ans[j] = b[j] = 0;
        }
        Ans = ans[m];
        For (i, 1, m) mul(Ans, i);
        printf("%d", Ans);
    }

    return 0;
}
