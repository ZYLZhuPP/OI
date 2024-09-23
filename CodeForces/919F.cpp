#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505;

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
	inline bool operator ~ () const { return ~c; }
} io;

int T, id[9][9][9][9], c[N][5], cnt[N], f[N][N], d[N][N], tot;

inline void dfs(int x, int y) {
    For (i, 0, 4) For (j, 1, 4) if (i ^ j && c[y][i] && c[x][j]) {
        int k = (i - j + 5) % 5;
        int t[5]; memcpy(t, c[y], sizeof t); t[i]--; t[k]++;
        int X = id[t[1]][t[2]][t[3]][t[4]], Y = x;
        if (~f[X][Y]) continue;
        if (!f[x][y]) f[X][Y] = 1, dfs(X, Y);
        else if (++d[X][Y] == cnt[X] * cnt[Y]) f[X][Y] = 0, dfs(X, Y);
    }
}

inline void init() {
    For (i1, 0, 8) For (i2, 0, 8 - i1) For (i3, 0, 8 - i1 - i2) For (i4, 0, 8 - i1 - i2 - i3) {
        c[tot][0] = 8 - (c[tot][1] = i1) - (c[tot][2] = i2) - (c[tot][3] = i3) - (c[tot][4] = i4);
        cnt[id[i1][i2][i3][i4] = tot++] = (i1>0) + (i2>0) + (i3>0) + (i4>0);
    }
    memset(f, -1, sizeof f);
    For (i, 1, tot - 1) f[0][i] = 1, f[i][0] = 0, dfs(i, 0);
}

int main() {
    init();
    io >> T;
    while (T--) {
        int flag, t[2][5], x, y; memset(t, 0, sizeof t);
        io >> flag;
        For (i, 0, 1) For (j, 1, 8) io >> x, t[i][x]++;
        x = id[t[0][1]][t[0][2]][t[0][3]][t[0][4]], y = id[t[1][1]][t[1][2]][t[1][3]][t[1][4]];
        if (flag) swap(x, y);
        puts(~f[x][y]? f[x][y] ^ flag? "Alice": "Bob": "Deal");
    }

    return 0;
}
