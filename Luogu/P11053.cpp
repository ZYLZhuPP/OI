#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 4e5 + 5;

int n, M, q;
vector<ll > s[N];
ll s1[N], s2[N];

inline ll calc(int x, int X, int y, int Y) { return s[X][Y] - s[x - 1][Y] - s[X][y - 1] + s[x - 1][y - 1]; }

inline ll solve(int a, int b, int c, int d) {
    int x[4] = {a, b, c, d}; sort(x, x + 4);
    ll res = (x[1] - x[0] + 1) * (s1[x[2]] - s1[x[1] - 1]);
    res += (1 - x[0]) * (s1[x[1] - 1] - s1[x[0] - 1]) + s2[x[1] - 1] - s2[x[0] - 1];
    res += (x[3] + 1) * (s1[x[3]] - s1[x[2]]) - s2[x[3]] + s2[x[2]];
    return res;
}

vector<ll > mosaic(vector<int > X, vector<int > Y, vector<int > T, vector<int > B, vector<int > L, vector<int > R) {
    n = X.size(); M = min(4, n);
    For (i, 0, M) s[i].resize(n + 1, 0);
    For (i, M + 1, n) s[i].resize(M + 1, 0);
    For (i, 1, n) s[1][i] = X[i - 1], s[i][1] = Y[i - 1];
    For (i, 2, n) For (j, 2, i<=M? n: M) s[i][j] = !(s[i - 1][j] | s[i][j - 1]);
    For (i, 0, 2 * n) s1[i] = s2[i] = 0;
    For (i, M, n) s1[i - M + n] = s2[i - M + n] = s[i][M];
    For (i, M, n) s1[M - i + n] = s2[M - i + n] = s[M][i];
    For (i, 1, n) For (j, 1, i<=M? n: M) s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    For (i, M, 2 * n - M) s1[i] += s1[i - 1], s2[i] = s2[i - 1] + i * s2[i];
    q = T.size();
    vector<ll > ans;
    For (i, 0, q - 1) {
        int x = T[i] + 1, X = B[i] + 1, y = L[i] + 1, Y = R[i] + 1;
        ll res = 0;
        if (X <= M || Y <= M) { ans.pb(calc(x, X, y, Y)); continue; }
        if (x <= M) res += calc(x, M, y, Y), x = M + 1;
        if (y <= M) res += calc(x, X, y, M), y = M + 1;
        ans.pb(res + solve(x - y + n, x - Y + n, X - y + n, X - Y + n));
    }
    return ans;
}