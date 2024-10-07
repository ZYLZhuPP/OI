#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

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

namespace Basis {
    int o[18];
    inline bool ins(int x) {
        rFor (i, 17, 0) if (x >> i & 1) {
            if (!o[i]) return o[i] = x, 1;
            x ^= o[i];
        }
        return 0;
    }
}
using namespace Basis;

int K, n;
ll ans;
array<int, 2 > a[N];

int main() {
    io >> K; n = (1 << K) - 1;
    int x;
    For (i, 1, n) io >> x, a[i] = {x, i};
    sort(a + 1, a + n + 1);
    For (i, 1, n) if (ins(a[i][1])) ans += a[i][0];
    printf("%lld", ans);

    return 0;
}
