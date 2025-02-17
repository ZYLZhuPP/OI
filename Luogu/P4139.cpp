#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e7 + 5;

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

int T, mip[N], phi[N], pri[N], ps;

void init() {
    For (i, 2, 1e7) {
        if (!mip[i]) phi[i] = i - 1, pri[mip[i] = ++ps] = i;
        For (j, 1, mip[i]) {
            int x = i * pri[j];
            if (x > 1e7) break;
            if (j == mip[i]) phi[x] = phi[i] * pri[j];
            else phi[x] = phi[i] * (pri[j] - 1);
            mip[x] = j;
        }
    }
}

inline int qPow(int a, int b, int p) {
    int r = 1;
    while (b) {
        if (b & 1) r = 1ll * r * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return r;
}

inline int solve(int p) {
    if (p == 1) return 0;
    return qPow(2, solve(phi[p]) + phi[p], p);
}

int main() {
    init();
    io >> T;
    int p;
    while (T--) io >> p, printf("%d\n", solve(p));

    return 0;
}
