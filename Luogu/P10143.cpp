#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 205, M = 3e5 + 5, Mo = 998244353;
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

int ID, n, T, _2[N], f[M], a[N], t[N], ans;
ll s[N];

int main() {
    io >> ID >> n >> T;
    _2[0] = 1; For (i, 1, n) _2[i] = mo(_2[i - 1] << 1);
    For (i, 1, n) io >> a[i];
    For (i, 1, n) io >> t[i], s[i] = s[i - 1] + t[i];
    f[0] = 1;
    For (i, 1, n) {
        int x = 0; For (j, 0, T - t[i]) add(x, f[j]);
        add(ans, ml(a[i], ml(_2[n - i], x)));
        rFor (j, T, t[i]) add(f[j], f[j - t[i]]);
    }
    memset(f, 0, sizeof f); f[0] = 1;
    rFor (i, n, 1) {
        int x = 0; For (j, 0, T - s[i]) add(x, f[j]);
        add(ans, ml(a[i], ml(_2[i - 1], x)));
        rFor (j, T, t[i]) add(f[j], f[j - t[i]]);
    }
    printf("%d", ans);

    return 0;
}
