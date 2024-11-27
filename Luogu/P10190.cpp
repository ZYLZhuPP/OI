#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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

int T, n, x0, A, B, ka[N], kb[N], c[N];
array<int, 2 > a[N], b[N];
ll K[N];

inline bool ok(array<int, 2 > p[], int k[], int n, ll y) {
    For (i, 1, n) K[i] = (p[i][1] - y) / p[i][0];
    sort(K + 1, K + n + 1);
    For (i, 1, n) if (k[i] > K[i]) return 0;
    return 1;
}

inline ll solve(array<int, 2 > p[], int k[], int n) {
    ll l = -1e18, r = 1e18, res = -1e18;
    while (l <= r) {
        ll m = (l + r) >> 1;
        if (ok(p, k, n, m)) res = m, l = m + 1;
        else r = m - 1;
    }
    return res;
}

int main() {
    io >> T;
    while (T--) {
        io >> n >> x0;
        int y, Y, x;
        For (i, 1, n) {
            io >> y >> Y >> x;
            a[i] = {x, y}; b[i] = {x, -Y};
            c[i * 2 - 1] = y; c[i * 2] = Y;
        }
        A = 0; B = 0;
        For (i, 1, 4 * n) {
            io >> x;
            if (x > 0) ka[++A] = x;
            else kb[++B] = -x;
        }
        if (A < n || B < n) { puts("-1"); continue; }
        sort(ka + 1, ka + A + 1); sort(kb + 1, kb + B + 1);
        sort(c + 1, c + 2 * n + 1);
        For (i, 1, A - n) a[n + i] = {x0, c[2 * n - i + 1]};
        For (i, 1, B - n) b[n + i] = {x0, -c[i]};
        printf("%lld\n", -(solve(a, ka, A) + solve(b, kb, B)));
    }

    return 0;
}
