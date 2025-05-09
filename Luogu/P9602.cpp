#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

int a[N][N], L[N][N], R[N][N], U[N][N], f[N][N];

int biggest_stadium(int N, vector<vector<int > > F) {
    int n = N, ans = 0;
    For (i, 0, n + 1) a[0][i] = a[n + 1][i] = a[i][0] = a[i][n + 1] = 1;
    For (i, 1, n) For (j, 1, n) a[i][j] = F[i - 1][j - 1];
    vector<array<int, 2 > > dp[n + 1];
    For (i, 0, n + 1) {
        For (j, 0, n + 1) if (a[i][j]) L[i][j] = j, U[i][j] = i; else L[i][j] = L[i][j - 1], U[i][j] = U[i - 1][j];
        rFor (j, n + 1, 0) if (a[i][j]) R[i][j] = j; else R[i][j] = R[i][j + 1];
        For (j, 1, n) if (!a[i][j]) dp[i - U[i][j]].pb({i, j});
    }
    For (len, 1, n) {
        for (auto &[i, j] : dp[len]) {
            if (a[i - 1][j]) {
                f[i][j] = R[i][j] - L[i][j] - 1;
                cmax(ans, f[i][j]);
                continue;
            }
            cmax(L[i][j], L[i - 1][j]); cmin(R[i][j], R[i - 1][j]);
            int D = R[i][j] - L[i][j] - 1;
            f[i][j] = f[i - 1][j] + D;
            cmax(f[i][j], f[i][L[i - 1][j]] + (U[i][L[i - 1][j]] - U[i][j]) * D);
            cmax(f[i][j], f[i][R[i - 1][j]] + (U[i][R[i - 1][j]] - U[i][j]) * D);
            cmax(ans, f[i][j]);
        }
    }
    return ans;
}
