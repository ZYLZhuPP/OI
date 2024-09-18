#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;

int n, m, a[N][N], c[5 * N], ans;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    For (i, 1, n) For (j, 1, m) cin >> a[i][j];
    For (i, 1, n) {
        int s = 0, x, l;
        For (j, 1, m) c[a[i][j]] = 1;
        cin >> l;
        For (j, 1, l) cin >> x, s += c[x];
        if (s == m) ans += 2;
        For (j, 1, m) c[a[i][j]] = 0;
    }
    cout << ans;

    return 0;
}
