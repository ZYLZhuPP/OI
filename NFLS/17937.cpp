#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 998244353;
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

int n, m, inv[N], fac[N], ivf[N], a[N], s[N], f[N];
bool ok[N];

int main() {
    io >> n >> m;
    inv[1] = 1; For (i, 2, n) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    fac[0] = ivf[0] = 1; For (i, 1, n) fac[i] = ml(fac[i - 1], i), ivf[i] = ml(ivf[i - 1], inv[i]);
    For (i, 1, n) io >> a[i], s[a[i]]++;
    sort(a + 1, a + n + 1);
    For (i, 1, max(m, a[n])) s[i] += s[i - 1];
    ok[m] = 1; f[m] = ml(fac[s[a[n]]], ivf[s[m]]);
    rFor (i, m, 1) if (ok[i]) {
        For (j, 1, n) if (a[j] <= i) {
            int x = i % a[j];
            ok[x] = 1;
            add(f[x], ml(f[i], ml(fac[s[i] - 1], ivf[s[x]])));
        }
    }
    rFor (i, a[1] - 1, 0) if (ok[i]) { printf("%d\n%d", i, f[i]); break; }

    return 0;
}