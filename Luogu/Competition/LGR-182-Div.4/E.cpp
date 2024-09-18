#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;

int n, m, k, a[N][N], H[N][N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    memset(H, 127, sizeof H);
    cin >> n >> m >> k;
    For (i, 1, k) {
        int x, y, h, c;
        cin >> x >> y >> h >> c;
        if (H[x][y] > h) a[x][y] = c, H[x][y] = h;
    }
    For (i, 1, n) { For (j, 1, m) cout << a[i][j] << " "; cout << endl; }

    return 0;
}
