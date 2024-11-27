#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef long double Lf;

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

int T, ans, n, K;

int main() {
    io >> T;
    while (T--) {
        io >> n >> K;
        Lf k = sqrt(Lf(K));
        int x = k;
        if (x * x == K) {
            if (x & 1) printf("%d\n", -(n & 1));
            else printf("%d\n", n);
            continue;
        }
        ans = 0;
        For (i, 1, n) ans += ll(i * k)&1? -1: 1;
        printf("%d\n", ans);
    }

    return 0;
}
