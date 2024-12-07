#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e4 + 5;

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
    inline bool operator ~ () { return ~c; }
} io;

int n, x, y, a[N], b[N], ans;

int main() {
    io >> n >> x >> y;
    For (i, 1, n) io >> a[i] >> b[i];
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
    For (i, 1, n) ans += a[i]<b[i]? (b[i] - a[i]) * x: (a[i] - b[i]) * y;
    printf("%d", ans);

    return 0;
}