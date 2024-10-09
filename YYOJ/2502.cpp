#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 105, M = 65;
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

int n, m, F[N][M][2][2];
ll f[M][N][N][2][2][2][2], L[N], R[N];

inline int get(ll x, int k) { return x >> (k - 1) & 1; }

inline ll dfs(int k, int l, int r, int l1, int l2, int r1, int r2) {
    ll &res = f[k][l][r][l1][l2][r1][r2];
    if (~res) return res;
    if (k > m) return res = 0;
    res = 1e18;
    int lv = get(l1? R[l - 1]: L[l - 1], k) ^ l2;
    int rv = get(r1? R[r + 1]: L[r + 1], k) ^ r2;
    if (l > r) return res = dfs(k + 1, l, r, l1, 0, r1, 0) + F[r][k][lv][rv];
    ll g[2]; g[0] = g[1] = 1e18; g[lv] = 0;
    bool flag = 1;
    For (i, l, r + 1) {
        ll g0 = g[0], g1 = g[1];
        For (j, 0, 1) g[j] = min(g0 + F[i - 1][k][0][j], g1 + F[i - 1][k][1][j]);
        if (i > r) break;
        For (j, 0, 1) {
            if (k == 1) cmin(res, dfs(k, l, i - 1, l1, l2, j, 0) + dfs(k, i + 1, r, j, 0, r1, r2));
            if ((L[i] >> k) != (R[i] >> k) && !((!j && get(L[i], k)) || (j && !get(R[i], k)))) cmin(res, dfs(k, l, i - 1, l1, l2, j, 1) + dfs(k, i + 1, r, j, 1, r1, r2));
        }
        if ((L[i] >> k) == (R[i] >> k)) { flag = 0; break; }
    }
    if (flag) cmin(res, g[rv] + dfs(k + 1, l, r, l1, 0, r1, 0));
    return res;
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> L[i] >> R[i];
    For (i, 1, n - 1) For (j, 1, m) For (k, 0, 1) For (l, 0, 1) io >> F[i][j][k][l];
    memset(f, -1, sizeof f);
    printf("%lld", dfs(1, 1, n, 0, 0, 0, 0));

    return 0;
}
