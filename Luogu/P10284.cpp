#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;
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

int n, q, a[N];
ll s[N], s_[N];
array<int, 2 > f[N][18];

inline array<int, 2 > find(int L, int R, int x) {
    bool flip = x < 1; if (flip) x = 1 - x;
    int l = lower_bound(s + L, s + R + 1, x + s[L]) - s - 1, r;
    x -= s[l] - s[L]; L = l;
    if (L < R) {
        int k = L&1? 1: -1;
        l = 1, r = (R - L) / 2 + 1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (x - k * (s_[L + 2 * m] - s_[L]) < 1) r = m;
            else l = m + 1;
        }
        cmin(R, L + 2 * r - 1);
        l = 1, r = (R - L - 1) / 2 + 1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (x - k * (s_[L + 2 * m + 1] - s_[L]) > 0) r = m;
            else l = m + 1;
        }
        cmin(R, L + 2 * r);
        x -= k * (s_[R] - s_[L]);
    }
    if (flip) x = 1 - x;
    return {R, x};
}

inline array<int, 2 > F(int l, int i, int j) {
    if (l == n) return {l, i};
    bool flip = i < 1; if (flip) i = 1 - i;
    auto [x, y] = f[i][j]; if (flip) y = 1 - y;
    return {x, y};
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], s[i] = s[i - 1] + a[i], s_[i] = s_[i - 1] + (i&1? -1: 1) * a[i];
    rFor (i, n, 1) For (j, a[i + 1] + 1, a[i]) {
        f[j][0] = find(i, n, j);
        For (k, 1, 17) f[j][k] = F(f[j][k - 1][0], f[j][k - 1][1], k - 1);
    }
    io >> q;
    int l, r, x;
    while (q--) {
        io >> l >> r >> x; l--;
        auto [L, X] = find(l, r, x);
        if (L < r) rFor (i, 17, 0) {
            auto [R, Y] = F(L, X, i);
            if (R <= r) L = R, X = Y;
        }
        printf("%d\n", find(L, r, X)[1]);
    }

    return 0;
}
