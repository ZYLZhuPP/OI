#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105;

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
	inline bool operator ~ () {return ~c;}
} io;

int n, m, q, c[N][N][4], mp[256], X, Y, vis[N][N], ans, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char st[N];

inline bool dfs(int x, int y, int s) {
    vis[x][y] = s;
    if (x == X && y == Y) return 1;
    bool res = 0;
    For (i, 0, 3) if (s >> c[x][y][i] & 1) {
        int a = x + dx[i], b = y + dy[i];
        if (a > 0 && a <= n && b > 0 && b <= m && vis[a][b] ^ s) res |= dfs(a, b, s);
    }
    return res;
}

int main() {
    mp['C'] = 1; mp['Z'] = 2; mp['N'] = 3;
    io >> n >> m;
    For (i, 1, n) {
        scanf("%s", st + 1);
        For (j, 1, m - 1) c[i][j][0] = c[i][j + 1][1] = mp[st[j]];
    }
    For (i, 1, n - 1) {
        scanf("%s", st + 1);
        For (j, 1, m) c[i][j][2] = c[i + 1][j][3] = mp[st[j]];
    }
    io >> q;
    while (q--) {
        memset(vis, -1, sizeof vis);
        ans = 4;
        int a, b;
        io >> a >> b >> X >> Y;
        For (s, 0, 14) if (dfs(a, b, s)) ans = min(ans, __builtin_popcount(s));
        printf("%d\n", ans);
    }

    return 0;
}
