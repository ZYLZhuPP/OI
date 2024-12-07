#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

int n, a[N], B, m, bl[450], br[450], be[N], ans, to[N], w[N];

inline void upd(int i) {
    rFor (j, br[i], bl[i]) {
        if (j + a[j] > br[i]) to[j] = j + a[j], w[j] = 1;
        else to[j] = to[j + a[j]], w[j] = w[j + a[j]] + 1;
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    B = sqrt(n);
    For (i, 1, B) bl[i] = br[i - 1] + 1, br[i] = i * B;
    br[B] = n;
    For (i, 1, B) For (j, bl[i], br[i]) be[j] = i;
    For (i, 1, B) upd(i);
    io >> m;
    int op, x, k;
    while (m--) {
        io >> op >> x; x++;
        if (op == 1) {
            ans = 0;
            while (x <= n) ans += w[x], x = to[x];
            printf("%d\n", ans);
        } else if (op == 2) {
            io >> k;
            a[x] = k;
            upd(be[x]);
        }
    }

    return 0;
}