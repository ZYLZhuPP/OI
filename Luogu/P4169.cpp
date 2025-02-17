#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;
inline void cmax(int &x, const int &y) { x = y>x? y: x; }
inline void cmin(int &x, const int &y) { x = y<x? y: x; }

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

int n, m, ans[N], op[N];

struct OP {
    int x, y, z;
    bool operator < (const OP &a) const { return x^a.x? x<a.x: y^a.y? y<a.y: z<a.z; }
} a[N], b[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void add(int x, const int &v) { for (x++; x < N; x += lowbit(x)) cmax(o[x], v); }
    inline void del(int x) { for (x++; x < N; x += lowbit(x)) o[x] = -2e6; }
    inline int query(int x) { int r = -2e6; for (x++; x; x -= lowbit(x)) cmax(r, o[x]); return r; }
}
using namespace BIT;

inline void cdq(int l, int r) {
    if (l == r) return;
    int m = (l + r) >> 1;
    cdq(l, m); cdq(m + 1, r);
    for (int i = l, j = l, k = m + 1; i <= r; ++i) {
        if (j <= m && (k > r || a[j].y <= a[k].y)) {
            b[i] = a[j++];
            if (op[b[i].z] == 1) add(b[i].z, b[i].x + b[i].y);
        } else {
            b[i] = a[k++];
            if (op[b[i].z] == 2) cmin(ans[b[i].z], b[i].x + b[i].y - query(b[i].z));
        }
    }
    For (i, l, r) { a[i] = b[i]; if (op[b[i].z] == 1) del(b[i].z); }
}

void solve() {
    sort(a + 1, a + n + m + 1);
    cdq(1, n + m);
}

int main() {
    memset(o, 224, sizeof o);
    memset(ans, 127, sizeof ans);
    io >> n >> m;
    int x, y;
    op[0] = 1; For (i, 1, n) io >> x >> y, a[m + i] = {x, y, 0};
    For (i, 1, m) io >> op[i] >> x >> y, a[i] = {x, y, i};
    solve(); for (auto &x : a) x.x = 1e6 - x.x;
    solve(); for (auto &x : a) x.y = 1e6 - x.y;
    solve(); for (auto &x : a) x.x = 1e6 - x.x;
    solve();
    For (i, 1, m) if (op[i] == 2) printf("%d\n", ans[i]);

    return 0;
}
