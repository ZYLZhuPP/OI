#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;

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

struct Basis {
    ll o[62];
    Basis() { memset(o, 0, sizeof o); }
    inline bool ins(ll x) {
        rFor (i, 61, 0) if (x >> i & 1) {
            if (!o[i]) return o[i] = x, 1;
            x ^= o[i];
        }
        return 0;
    }
};

int T, n, m, q;

int main() {
    io >> T;
    while (T--) {
        Basis A; int rank = 0;
        io >> n >> m >> q;
        ll x;
        while (m--) io >> x, rank += A.ins(x << 1 | 1);
        while (q--) {
            io >> x;
            Basis B = A; int k = rank + B.ins(x << 1 | 1);
            printf("%lld\n", B.ins(1)? 1ll << (n - k): 0);
        }
    }

    return 0;
}
