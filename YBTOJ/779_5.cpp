#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5, _N = 40, M = 2e4 + 5;

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

int n, m, Q, a[N], S, B, bl[N], br[N], be[N], b[M], cnt[_N][_N][M], f[_N][_N][M], ans;

void init() {
    S = pow(n, 2.0 / 3);
    B = n / S; if (B * S < n) B++;
    For (i, 1, B) bl[i] = br[i - 1] + 1, br[i] = i * S;
    br[B] = n;
    For (i, 1, B) For (j, bl[i], br[i]) be[j] = i;
    For (i, 1, B) {
        For (j, i, B) {
            For (k, bl[j], br[j]) b[a[k]]++;
            For (k, 1, m) cnt[i][j][k] = b[k], f[i][j][k] = f[i][j][k - 1] + b[k] * b[k];
        }
        For (j, bl[i], n) b[a[j]]--;
    }
}

int query(int l, int r, int x, int y) {
    int L = be[l], R = be[r], res = 0;
    if (L == R) {
        For (i, l, r) {
            int o = a[i], d = b[o] << 1 | 1;
            if (x <= o && o <= y) res += d, b[o]++;
        }
        For (i, l, r) b[a[i]] -= x <= a[i] && a[i] <= y;
    } else {
        res = f[L + 1][R - 1][y] - f[L + 1][R - 1][x - 1];
        For (i, l, br[L]) {
            int o = a[i], d = (b[o] + cnt[L + 1][R - 1][o]) << 1 | 1;
            if (x <= o && o <= y) res += d, b[o]++;
        }
        For (i, bl[R], r) {
            int o = a[i], d = (b[o] + cnt[L + 1][R - 1][o]) << 1 | 1;
            if (x <= o && o <= y) res += d, b[o]++;
        }
        For (i, l, br[L]) b[a[i]] -= x <= a[i] && a[i] <= y;
        For (i, bl[R], r) b[a[i]] -= x <= a[i] && a[i] <= y;
    }
    return res;
}

int main() {
    io >> n >> m >> Q;
    For (i, 1, n) io >> a[i];
    init();
    while (Q--) {
        int l, r, a, b;
        io >> l >> r >> a >> b;
        l ^= ans; r ^= ans; a ^= ans; b ^= ans;
        printf("%d\n", ans = query(l, r, a, b));
    }

    return 0;
}
