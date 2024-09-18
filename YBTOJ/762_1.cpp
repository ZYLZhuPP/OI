#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 805, inf = 1e9;

int T, n, m, a[N][N];

namespace Seg_Seg {
    int mx[N << 1][N << 1], mn[N << 1][N << 1];
    inline void up(int x, int y) { mx[x][y] = max(mx[x][y << 1], mx[x][y << 1 | 1]), mn[x][y] = min(mn[x][y << 1], mn[x][y << 1 | 1]); }
    inline void Up(int x, int y) { mx[x][y] = max(mx[x << 1][y], mx[x << 1 | 1][y]), mn[x][y] = min(mn[x << 1][y], mn[x << 1 | 1][y]); }
    inline void Build() {
        memset(mx, 0, sizeof mx); memset(mn, 127, sizeof mn);
        For (x, 1, n) {
            int i = x + n;
            For (y, 1, n) {
                int j = y + n;
                mx[i][j] = mn[i][j] = a[x][y];
            }
            rFor (j, n, 1) up(i, j);
        }
        rFor (i, n, 1) For (j, 1, n << 1) Up(i, j);
    }
    inline void Upd(int x, int y, int v) {
        int i = x + n, j = y + n;
        mx[i][j] = mn[i][j] = v;
        while (j >>= 1) up(i, j);
        while (i >>= 1) {
            int j = y + n;
            do Up(i, j); while(j >>= 1);
        }
    }
    int Mx, Mn;
    inline void query(int x, int y, int Y) {
        for (int l = y + n - 1, r = Y + n + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (~l & 1) Mx = max(Mx, mx[x][l ^ 1]), Mn = min(Mn, mn[x][l ^ 1]);
            if (r & 1) Mx = max(Mx, mx[x][r ^ 1]), Mn = min(Mn, mn[x][r ^ 1]);
        }
    }
    inline int Query(int x, int X, int y, int Y) {
        Mx = 0; Mn = inf;
        for (int l = x + n - 1, r = X + n + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (~l & 1) query(l ^ 1, y, Y);
            if (r & 1) query(r ^ 1, y, Y);
        }
        //cout << Mx << " " << Mn << endl;
        return (Mx + Mn) >> 1;
    }
}
using namespace Seg_Seg;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> T;
    For (Case, 1, T) {
        cout << "Case #" << Case << ":\n";
        cin >> n;
        For (i, 1, n) For (j, 1, n) cin >> a[i][j];
        Build();
        cin >> m;
        while (m--) {
            int x, y, d, v;
            cin >> x >> y >> d; d >>= 1;
            v = Query(max(1, x - d), min(n, x + d), max(1, y - d), min(n, y + d));
            Upd(x, y, v);
            cout << v << endl;
        }
    }

    return 0;
}
