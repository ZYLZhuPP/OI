#include<bits/stdc++.h>
using namespace std;

#define pb push_back
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
    inline bool operator ~ () const { return ~c; }
} io;

int n, q, a[N], ans[N];
array<int, 2 > h[N];
array<int, 4 > qs[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x <= n; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

int main() {
    io >> n >> q;
    For (i, 1, n) io >> h[i][0], h[i][1] = i;
    int x, l, r;
    For (i, 1, q) io >> l >> r >> x, qs[i] = {x, l, r, i};
    sort(h + 1, h + n + 1); sort(qs + 1, qs + q + 1);
    int t = n;
    rFor (i, q, 1) {
        auto [x, l, r, id] = qs[i];
        while (h[t][0] > x) {
            int j = h[t--][1]; a[j] = 1;
            if (!a[j - 1]) upd(j, 1);
            if (a[j + 1]) upd(j + 1, -1);
        }
        ans[id] = query(r) - query(l) + a[l];
    }
    For (i, 1, q) printf("%d\n", ans[i]);

    return 0;
}
