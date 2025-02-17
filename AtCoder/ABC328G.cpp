#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 30, S = 1 << 22;
typedef long long ll;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n;
ll C, a[N], b[N], f[S];

int main() {
    io >> n >> C;
    For (i, 0, n - 1) io >> a[i];
    For (i, 0, n - 1) io >> b[i];
    memset(f, 31, sizeof f);
    f[0] = -C;
    For (s, 0, (1 << n) - 1) {
        int x = __builtin_popcount(s);
        For (i, 0, n - 1) if (!(s >> i & 1)) {
            int s_ = s; ll sum = C;
            For (j, i, n - 1) if (!(s >> j & 1)) {
                s_ |= 1 << j;
                sum += abs(a[j] - b[x + j - i]);
                cmin(f[s_], f[s] + sum);
            } else break;
        }
    }
    printf("%lld", f[(1 << n) - 1]);

    return 0;
}
