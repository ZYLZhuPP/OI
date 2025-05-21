#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll inf = 1e18;
const int N = 1e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

ll f[2][N];
vector<array<int, 2 > > a[N], vis[N];

ll max_weights(int N, int M, vector<int > X, vector<int > Y, vector<int > W) {
    int n = N, m = M;
    For (i, 0, m - 1) vis[Y[i]].pb({X[i], W[i]});
    For (i, 0, n - 1) for (auto [x, w] : vis[i]) a[x].pb({i, w});
    For (i, 0, n - 1) a[i].pb({n, 0});
    For (i, 1, n - 1) {
        int k1 = a[i - 1].size(), k2 = a[i].size();
        ll s1 = 0, s2 = 0, mx1 = -inf, mx2 = -inf, mx3 = -inf;
        for (int j = 0, j1 = 0; j < k1; j++) {
            while (j1 < k2 && a[i - 1][j][0] > a[i][j1][0]) s2 += a[i][j1++][1];
            cmax(mx1, f[0][j] - s1); cmax(mx2, f[1][j]); cmax(mx3, f[1][j] + s2);
            s1 += a[i - 1][j][1];
        }
        s1 = s2 = 0;
        for (int j = 0, j1 = 0; j < k2; j++) {
            while (j1 < k1 && a[i][j][0] > a[i - 1][j1][0]) s1 += a[i - 1][j1++][1];
            f[0][j] = max(mx1 + s1, mx2); f[1][j] = max(f[0][j], mx3 - s2);
            s2 += a[i][j][1];
        }
    }
    ll ans = 0;
    For (i, 0, (int)a[n - 1].size() - 1) cmax(ans, f[1][i]);
    return ans;
}
