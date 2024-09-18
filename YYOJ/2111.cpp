#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef __int128 lll;
const int N = 2e7 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int num, T, l, r, s[N];

inline bool ok(int a, int b) { return a >= b && b == a / (a / b); }

void init() {
    int x = 2;
    s[1] = x;
    For (i, 2, N - 1) {
        while (!ok(i, x - 1)) x--;
        while (ok(i, x)) x++;
        s[i] = mo(s[i - 1] + x);
    }
}

int main() {
    init();
    io >> num;
    io >> T;
    while (T--) {
        io >> l >> r;
        printf("%d\n", mo(s[r] - s[l - 1]));
    }

    return 0;
}
