#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 205, M = 2e4 + 5;

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

int n, a[N], b[N], A, B;
bitset<M > f, g[N], ans;

int main() {
    io >> n;
    if (n == 1) return puts("1"), 0;
    int x;
    For (i, 1, n) {
        io >> x;
        if (x & 1) a[++A] = x;
        else b[++B] = x;
    }
    f[0] = 1;
    For (i, 1, B) f |= f << b[i];
    g[0][0] = 1;
    For (i, 1, A) rFor (j, (A + 1) / 2, 1) g[j] |= g[j - 1] << a[i];
    For (i, 0, M - 1) if (g[(A + 1) / 2][i]) ans |= f << i;
    printf("%d", (int)ans.count() - max(0, 2 - A));

    return 0;
}
