#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e6 + 5;

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
    inline bool operator ~ () const { return ~c; }
} io;

int n, q, a[N], cntb[33], cntc[33], x, y, b[33], c[33];

void upd(int k, int d) {
    int x = a[k], y = a[k + 1];
    For (i, 0, 30) b[i] = x & 1, c[i] = y & 1, x >>= 1, y >>= 1;
    rFor (i, 30, 0) {
        if (b[i] ^ c[i]) {
            if (b[i] > c[i]) cntb[i] += d;
            else cntc[i] += d;
            break;
        }
    }
}

void solve() {
    bool ok = 1;
    int ans = 0;
    For (i, 0, 30) {
        if (cntb[i] && cntc[i]) { ok = 0; break; }
        if (cntb[i]) ans += 1 << i;
    }
    if (ok) printf("%d\n", ans);
    else puts("-1");
}

int main() {
    io >> n;
    For (i, 1, n) {
        io >> a[i];
        if (i > 1) upd(i - 1, 1);
    }
    solve();
    io >> q;
    while (q--) {
        io >> x >> y;
        if (x > 1) upd(x - 1, -1);
        if (x < n) upd(x, -1);
        a[x] = y;
        if (x > 1) upd(x - 1, 1);
        if (x < n) upd(x, 1);
        solve();
    }

    return 0;
}
