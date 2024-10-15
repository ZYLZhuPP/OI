#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 3e5 + 5;
template<class C > inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

int n, a[N], b[N], ans;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    bool operator ~ () const { return ~c; }
} io;

inline int calc(int x) {
    int s = 0, mx = 0, Mx = 0;
    For (i, 1, n) {
        s += a[i] >= x;
        mx = max(0, mx + (b[i]>=x) - (a[i]>=x));
        cmax(Mx, mx);
    }
    return s + Mx;
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i] >> b[i];
    int l = 1, r = 1e9;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (calc(m) >= (n + 1) >> 1) ans = m, l = m + 1;
        else r = m - 1;
    }
    printf("%d", ans);

    return 0;
}
