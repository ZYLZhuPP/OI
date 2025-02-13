#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i) 
#define vec vector

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
	inline IO& operator >> (char &x) {
		while ((c = gc()) < 33 && ~c);
		x = c; return *this;
	}
	inline bool operator ~() {return ~c;}
} io;

vec<int > s(1);
vec<vec<bool > > g;
vec<vec<vec<bool > > > vis;
vec<vec<vec<int > > > co, c;
int n, m, cnt, color, q, X, Y, D;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1}, Rx[4] = {0, 0, -1, 1}, Ry[4] = {1, -1, 0, 0};
int R[4] = {3, 2, 0, 1}, L[4] = {2, 3, 1, 0};
int Der[256];

void dfs(int x, int y, int d) {
	if (vis[x][y][d] && x == X && y == Y && d == D) {
		s.push_back(cnt);
		color++;
		cnt = 0;
		return;
	}
	
	if (!vis[x][y][d]) {
		vis[x][y][d] = 1;
		c[x][y][d] = cnt;
		co[x][y][d] = color;
	}
	int xx = x + Rx[d], yy = y + Ry[d], dd = R[d];
	if (g[xx][yy]) {
		vis[x][y][dd] = 1;
		co[x][y][dd] = color;
		c[x][y][dd] = cnt;
		cnt++;
		dfs(xx, yy, dd);
	} else {
		xx = x + dx[d], yy = y + dy[d];
		if (g[xx][yy]) {
			cnt++;
			dfs(xx, yy, d);
		} else 
			dfs(x, y, L[d]);
	}
}

void init() {
	Der['U'] = 0; Der['D'] = 1; Der['L'] = 2; Der['R'] = 3;
	g.resize(n + 2, vec<bool >(m + 2, 0));
	vis.resize(n + 2, vec<vec<bool > >(m + 2, vec<bool >(4, 0)));
	co.resize(n + 2, vec<vec<int > >(m + 2, vec<int >(4, 0)));
	c.resize(n + 2, vec<vec<int > >(m + 2, vec<int >(4, 0)));
}

int main() {
	io >> n >> m;
	init();
	For (i, 1, n) {
		For (j, 1, m) {
			char x;
			io >> x;
			g[i][j] = x == '.';
		}
	}
	
	color = 1;
	For (i, 1, n) {
		For (j, 1, m) if (g[i][j]) {
			For (d, 0, 3) if (!vis[i][j][d] && !g[i + Rx[d]][j + Ry[d]]) {
				X = i, Y = j, D = d;
				dfs(i, j, d);
			}
		}
	}
	
	io >> q;
	while (q--) {
		int sx, sy, tx, ty; char der;
		io >> sx >> sy >> tx >> ty >> der;
		int d = Der[der];
		int ans = 4 * n * m;
		For (i, 0, 3) if (co[sx][sy][d] == co[tx][ty][i]) {
			int x = co[sx][sy][d];
			ans = min(ans, (c[tx][ty][i] - c[sx][sy][d] + s[x]) % s[x]);
		}
		printf("%d\n", ans);
	}
	
	return 0;
}

