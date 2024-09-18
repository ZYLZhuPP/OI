#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef array<int, 2 > P;
const int N = 1e3 + 5;
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

const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m, l[N][N], up[N][N], dw[N][N], mx[N][N], dis[N][N], vis[N][N], tot, cnt, ans;
char g[N][N];

int main() {
    io >> n >> m;
    For (i, 1, n) {
        scanf("%s", g[i] + 1);
        For (j, 1, m) if (g[i][j] == '#') l[i][j] = 1 + l[i][j - 1], tot++;
    }
    For (i, 1, n) For (j, 1, m) up[i][j] = min((l[i][j] + 1) / 2, up[i - 1][j - 1] + 1);
    rFor (i, n, 1) For (j, 1, m) dw[i][j] = min((l[i][j] + 1) / 2, dw[i + 1][j - 1] + 1);
    For (i, 1, n) For (j, 1, m) mx[i][j] = min(up[i][j], dw[i][j]);
    int l = 0, r = n;
    while (l <= r) {
        queue<P > q; memset(dis, 31, sizeof dis); memset(vis, 0, sizeof vis); cnt = 0;
        int mid = (l + r) >> 1;
        For (i, 1, n) For (j, 1, m) if (mx[i][j] > mid) {
            int x = i, y = j - mid;
            q.push({x, y}), vis[x][y] = 1, dis[x][y] = 0, cnt++;
        }
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            if (dis[x][y] == mid) continue;
            For (k, 0, 3) {
                int a = x + dx[k], b = y + dy[k];
                if (g[a][b] == '#' && !vis[a][b]) dis[a][b] = dis[x][y] + 1, vis[a][b] = 1, cnt++, q.push({a, b});
            }
        }
        if (cnt == tot) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d", ans);

    return 0;
}
