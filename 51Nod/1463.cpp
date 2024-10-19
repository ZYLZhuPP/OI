#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, m, q, a[N], b[N], k[N], ans[N], pos[N];
vector<array<int, 2 > > qs[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int v) { for (; x; x -= lowbit(x)) cmax(o[x], v); }
    inline int query(int x) { int r = 0; for (; x < N; x += lowbit(x)) cmax(r, o[x]); return r; }
}
using namespace BIT;

int main() {
    io >> n >> q >> m;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) io >> b[i];
    For (i, 1, m) io >> k[i];
    int l, r;
    For (i, 1, q) io >> l >> r, qs[r].pb({l, i});
    For (i, 1, n) {
        pos[b[i]] = i;
        For (j, 1, m) {
            int x = pos[b[i] + k[j]];
            if (x) upd(x, a[x] + a[i]);
            if (b[i] > k[j]) {
                x = pos[b[i] - k[j]];
                if (x) upd(x, a[x] + a[i]);
            }
        }
        for (auto &[l, id] : qs[i]) ans[id] = query(l);
    }
    For (i, 1, q) printf("%d\n", ans[i]);

    return 0;
}
