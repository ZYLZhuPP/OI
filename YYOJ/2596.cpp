#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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

int n, a[N], f[N][N], s[N], q[N], t;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    s[0] = 1; a[0] = n + 1; q[++t] = 0;
    For (i, 1, n) {
        while (a[i] > a[q[t]]) t--;
        For (j, q[t] + 1, i) add(s[j], f[j][a[i]] = s[j - 1]);
        int x = 0;
        For (j, 1, t) add(x, f[i - 1][a[q[j]]]);
        rFor (j, t, 1) add(s[i], f[i][a[q[j]]] = x), add(x, -f[i - 1][a[q[j]]]);
        q[++t] = i;
    }
    printf("%d", s[n]);

    return 0;
}
