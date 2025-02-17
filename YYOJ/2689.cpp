#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
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

int K, n, m, nxt1[N], nxt2[N];
ll T, a[N], b[N], f[N][N], g[N][N];
ll sa[N], sb[N], F[N], G[N];

ll calc(int op, int x, int y, ll t) {
    ll res = 1e18, sum = 0;
    while (1) {
        if (x == n && y == m) {
            cmin(res, sum);
            break;
        }
        if (op) {
            while (x < n && a[x + 1] < t) sum += t - a[++x];
            if (x < n) cmin(res, sum + f[x + 1][y]);
            if (y == m) {
                cmin(res, sum);
                break;
            }
            if (b[y + 1] >= t + T) {
                cmin(res, sum + g[x][y + 1]);
                break;
            }
        } else {
            while (y < m && b[y + 1] < t) sum += t - b[++y];
            if (y < m) cmin(res, sum + g[x][y + 1]);
            if (x == n) {
                cmin(res, sum);
                break;
            }
            if (a[x + 1] >= t + T) {
                cmin(res, sum + f[x + 1][y]);
                break;
            }
        }
        op ^= 1; t += T;
    }
    return res;
}

int main() {
    io >> K >> T;
    char op[3]; ll x;
    For (i, 1, K) {
        scanf("%s", op); io >> x;
        if (op[0] == 'A') a[++n] = x;
        else b[++m] = x;
    }
    a[++n] = 0; sort(a + 1, a + n + 1);
    b[++m] = 0; sort(b + 1, b + m + 1);
    For (i, 1, n) sa[i] = sa[i - 1] + a[i];
    For (i, 1, m) sb[i] = sb[i - 1] + b[i];
    For (i, 1, n) For (j, 1, m) if (b[j] < a[i] + T) nxt1[i] = j;
    For (i, 1, m) For (j, 1, n) if (a[j] < b[i] + T) nxt2[i] = j;
    memset(f, 31, sizeof f); memset(g, 31, sizeof g);
    f[n][m] = g[n][m] = 0;
    rFor (i, n, 1) rFor (j, m, 1) {
        if (i == n && j == m) continue;
        if (j == nxt1[i]) F[i] = calc(0, i, j, a[i] + T);
        if (i == nxt2[j]) G[j] = calc(1, i, j, b[j] + T);
        cmin(f[i][j], f[i + 1][j]);
        if (b[j + 1] >= a[i] + T )cmin(f[i][j], g[i][j + 1]);
        else cmin(f[i][j], F[i] + (a[i] + T) * (nxt1[i] - j) - (sb[nxt1[i]] - sb[j]));
        cmin(g[i][j], g[i][j + 1]);
        if (a[i + 1] >= b[j] + T) cmin(g[i][j], f[i + 1][j]);
        else cmin(g[i][j], G[j] + (b[j] + T) * (nxt2[j] - i) - (sa[nxt2[j]] - sa[i]));
    }
    printf("%lld", min(f[1][1], g[1][1]));
    
    return 0;
}