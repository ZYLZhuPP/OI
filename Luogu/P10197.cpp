#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 305, S = 1 << 7;
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

int n, K, a[N], b[N], c[N], m, L[N], R[N], len[N], Len[S], f[N][N][S], ans;

int main() {
    io >> n >> K;
    a[0] = a[n + 1] = 1e6; ans = -2e6;
    For (i, 1, n) io >> a[i], ans += 2 * a[i];
    For (i, 1, K) io >> R[i], L[i] = R[i - 1], b[R[i]] = 1;
    K++; L[K] = R[K - 1]; R[K] = n + 1;
    For (i, 1, K) {
        len[i] = R[i] - L[i] - 1, L[i] = a[L[i]], R[i] = a[R[i]];
        if (L[i] > R[i]) swap(L[i], R[i]);
        if (!len[i]) ans += R[i] - L[i];
    }
    For (i, 1, n) if (!b[i]) c[++m] = a[i];
    sort(c + 1, c + m + 1);
    For (s, 0, (1 << K) - 1) For (i, 1, K) if (s >> (i - 1) & 1) Len[s] += len[i];
    memset(f, 31, sizeof f);
    For (s, 0, (1 << K) - 1) if (!Len[s]) For (l, 0, m + 1) For (r, 0, m + 1) f[l][r][s] = 0;
    For (i, 1, m) {
        For (l, 1, m - i + 1) {
            int r = l + i - 1;
            For (s, 0, (1 << K) - 1) {
                f[l][r][s] = min(f[l + 1][r][s], f[l][r - 1][s]);
                if (Len[s] > i) continue;
                if (Len[s] == i) {
                    For (j, 1, K) if (s >> (j - 1) & 1) {
                        if (len[j] == 1 && i == 1) f[l][r][s] = abs(L[j] - c[l]) + abs(R[j] - c[l]);
                        else if (len[j] > 1) cmin(f[l][r][s], f[l + 1][r - 1][s ^ (1 << (j - 1))] + abs(L[j] - c[l]) + abs(R[j] - c[r]) + c[r] - c[l]);
                    }
                }
                for (int t = (s - 1) & s; t; t = (t - 1) & s) cmin(f[l][r][s], f[l][l + Len[t] - 1][t] + f[l + Len[t]][r][s ^ t]);
            }
        }
    }
    ans += f[1][m][(1 << K) - 1]; ans /= 2;
    printf("%d", ans);

    return 0;
}
