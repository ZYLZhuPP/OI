#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 250, S = 1 << 5, inf = 1e9;
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

const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int T, n, m, K, C, Co[N], co[N], c[N][N], a[N][N], w[N][N], f[N][N][S], inq[N][N], ans1, ans2;
mt19937 rnd(1145141);

queue<array<int, 2 > > q;
inline void SPFA(int s) {
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop(); inq[x][y] = 0;
        For (k, 0, 3) {
            int a = x + dx[k], b = y + dy[k];
            if (a < 1 || a > n || b < 1 || b > m || !~c[a][b]) continue;
            if (cmin(f[a][b][s], f[x][y][s] + w[a][b]) && !inq[a][b]) q.push({a, b}), inq[a][b] = 1;
        }
    }
}

inline int solve() {
    int res = inf;
    For (o, 1, 200) {
        shuffle(Co + 1, Co + C + 1, rnd);
        For (i, 1, C) if (~Co[i]) co[Co[i]] = i % K;
        For (i, 1, n) For (j, 1, m) {
            For (s, 0, (1 << K) - 1) f[i][j][s] = inf;
            if (~c[i][j]) f[i][j][1 << co[c[i][j]]] = w[i][j];
        }
        For (s, 1, (1 << K) - 1) {
            For (i, 1, n) For (j, 1, m) if (~c[i][j]) {
                for (int t = s & (s - 1); t > (s ^ t); t = (t - 1) & s) cmin(f[i][j][s], f[i][j][t] + f[i][j][s ^ t] - w[i][j]);
                if (f[i][j][s] < inf) q.push({i, j}), inq[i][j] = 1;
            }
            SPFA(s);
        }
        For (i, 1, n) For (j, 1, m) cmin(res, f[i][j][(1 << K) - 1]);
    }
    return res;
}

int main() {
    io >> T;
    while (T--) {
        C = 0;
        io >> n >> m >> K;
        For (i, 1, n) For (j, 1, m) io >> c[i][j], Co[++C] = c[i][j];
        For (i, 1, n) For (j, 1, m) io >> a[i][j], w[i][j] = 1;
        sort(Co + 1, Co + C + 1); C = unique(Co + 1, Co + C + 1) - Co - 1;

        ans1 = solve();
        if (ans1 >= inf) { puts("-1 -1"); continue; }
        int l = 0, r = 1e6;
        while (l <= r) {
            int mid = (l + r) >> 1;
            For (i, 1, n) For (j, 1, m) w[i][j] = a[i][j]<=mid? 9999: 10001;
            if (solve() <= ans1 * 10000) ans2 = mid, r = mid - 1; else l = mid + 1;
        }
        printf("%d %d\n", ans1, ans2);
    }

    return 0;
}
