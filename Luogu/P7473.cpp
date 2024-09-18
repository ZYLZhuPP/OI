#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 255, M = 2e3 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () { return ~c; }
} io;

int n, m, Q, g[N][N], id[N][N], tot, to[N][N][4], dis[M][M];
vector<int > es[M][4];
queue<pair<int, int > > q;

inline bool check(int x, int y) { return g[x][y + 1] || g[x][y - 1] || g[x + 1][y] || g[x - 1][y]; }

int main() {
    io >> n >> m >> Q;
    For (i, 0, n + 1) g[0][i] = g[n + 1][i] = g[i][0] = g[i][n + 1] = 1;
    int x, y;
    For (i, 1, m) io >> x >> y, g[x][y] = 1;
    For (i, 1, n) For (j, 1, n) if (!g[i][j] && check(i, j)) id[i][j] = ++tot;
    For (i, 1, n) For (j, 1, n) if (!g[i][j])
        to[i][j][0] = g[i][j - 1]? id[i][j]: to[i][j - 1][0],
        to[i][j][1] = g[i - 1][j]? id[i][j]: to[i - 1][j][1];
    rFor (i, n, 1) rFor (j, n, 1) if (!g[i][j])
        to[i][j][2] = g[i][j + 1]? id[i][j]: to[i][j + 1][2],
        to[i][j][3] = g[i + 1][j]? id[i][j]: to[i + 1][j][3];
    For (i, 1, n) For (j, 1, n) if (id[i][j]) For (k, 0, 3) es[to[i][j][k]][k].pb(id[i][j]);
    memset(dis, 31, sizeof dis);
    For (i, 1, tot) dis[i][i] = 1, q.push({i, i});
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        For (k, 0, 3) for (auto &a : es[x][k]) for (auto &b : es[y][k]) if (cmin(dis[a][b], dis[x][y] + 1)) q.push({a, b});
    }
    while (Q--) {
        int a, b, c, d;
        io >> a >> b >> c >> d;
        if (a == c && b == d) puts("0");
        else {
            int ans = n * n;
            For (k, 0, 3) cmin(ans, dis[to[a][b][k]][to[c][d][k]]);
            printf("%d\n", ans<n*n? ans: -1);
        }
    }

    return 0;
}
