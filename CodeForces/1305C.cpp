#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;

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

int n, m, a[N], b[N], ans = 1;

int main() {
    io >> n >> m;
    For (i, 1, n) {
        io >> a[i];
        if (b[a[i] % m]++) return puts("0"), 0;
    }
    sort(a + 1, a + n + 1);
    For (i, 1, n) For (j, i + 1, n) ans = (a[j] - a[i]) % m * ans % m;
    printf("%d", ans);

    return 0;
}
