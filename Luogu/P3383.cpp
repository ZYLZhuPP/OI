#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e8 + 5;

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

int n, Q, k, mip[N], pri[N], psz;

void init() {
    For (i, 2, n) {
        if (!mip[i]) pri[mip[i] = ++psz] = i;
        For (j, 1, mip[i]) {
            if (i * pri[j] > n) break;
            mip[i * pri[j]] = j;
        }
    }
}

int main() {
    io >> n >> Q;
    init();
    while (Q--) io >> k, printf("%d\n", pri[k]);

    return 0;
}
