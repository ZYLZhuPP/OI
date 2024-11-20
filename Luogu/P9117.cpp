#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int T, n, m, q, xt[N], yt[N], xc[N], yc[N];

int main() {
    io >> T;
    while (T--) {
        io >> n >> m >> q;
        For (i, 1, n) xt[i] = xc[i] = 0;
        For (i, 1, m) yt[i] = yc[i] = 0;
        int op, x, c;
        For (i, 1, q) {
            io >> op >> x >> c;
            op? yt[x] = i, yc[x] = c: (xt[x] = i, xc[x] = c);
        }
        For (i, 1, n) For (j, 1, m) printf("%d%c", xt[i]>yt[j]? xc[i]: yc[j], " \n"[j==m]);
    }
    
    return 0;
}
