#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, m, K, B, q, a[N], b[N], mn[N][19], v[N], pre[N], lst[N];
set<int > pos[N];

inline int query(int l, int r) {
    if (l > r) return 2e9;
    int k = log2(r - l + 1);
    return min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

int main() {
    freopen("car.in", "r", stdin);
    freopen("car.out", "w", stdout);
    io >> n >> m >> K;
    int x;
    For (i, 1, m) io >> x >> v[i] >> a[i], b[i] = a[i];
    sort(b + 1, b + m + 1); B = unique(b + 1, b + m + 1) - b - 1;
    For (i, 1, m) pos[lower_bound(b + 1, b + B + 1, a[i]) - b].insert(v[i]);
    For (i, 1, B) {
        pre[i] = B + 1;
        for (auto &x : pos[i]) cmin(pre[i], lst[x]), lst[x] = i;
    }
    x = B; For (i, 2, n) cmin(x, lst[i]);
    For (i, x + 1, B) mn[i][0] = 2e9;
    int r = B, l, d;
    rFor (i, x, 1) {
        while (i <= pre[r]) r--;
        mn[i][0] = b[r] - b[i];
    }
    For (j, 1, 18) For (i, 1, B - (1 << j) + 1) mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
    io >> q;
    while (q--) {
        io >> l >> r >> d;
        int len = r - l + d, L = l - d, R = l;
        L = lower_bound(b + 1, b + B + 1, L) - b;
        R = upper_bound(b + 1, b + B + 1, R) - b - 1;
        puts((R < B && b[R + 1] - l <= len - mn[R + 1][0]) || query(L, R) <= len? "Yes": "No");
    }

    fclose(stdin); fclose(stdout);
    return 0;
}
