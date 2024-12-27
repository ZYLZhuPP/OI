#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)

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

int T, n;

int main() {
    io >> T;
    while (T--) {
        int c0 = 0, c1 = 0, c2 = 0;
        io >> n;
        int x;
        For (i, 1, n) {
            io >> x;
            if (x == 1) c1++;
            else if (x < 1) c0++;
            else c2++;
        }
        printf("%lld\n", 1ll * c0 * c1 + 1ll * c0 * c2 + 1ll * c1 * c2 + 1ll * c1 * (c1 - 1) / 2);
    }

    return 0;
}
