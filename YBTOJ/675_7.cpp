#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 205;

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

int n, m, X, Y, K, ans, f[N][N], f0[N];
int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };
int q[N];
char g[N][N];

inline void solve(int x, int y, int len, int dir) {
    int h = 1, t = 0;
    for (int i = 1; x && x <= n && y && y <= m; ++i, x += dx[dir], y += dy[dir]) {
        if (g[x][y] == 'x') h = 1, t = 0;
        else {
            f0[i] = f[x][y];
            while (h <= t && f0[q[t]] - q[t] < f0[i] - i) t--;
            q[++t] = i;
            while (h <= t && q[h] < i - len) h++;
            ans = max(ans, f[x][y] = f0[q[h]] + i - q[h]);
        }
    }
}
int main() {
    io >> n >> m >> X >> Y >> K;
    For (i, 1, n) scanf("%s", g[i] + 1);
    
    memset(f, -31, sizeof f); f[X][Y] = 0;
    For(i, 1, K) {
        int s, t, dir, len;
        io >> s >> t >> dir; dir--; len = t - s + 1;
        if (dir == 0) For (j, 1, m) solve(n, j, len, dir);
        else if (dir == 1) For (j, 1, m) solve(1, j, len, dir);
        else if (dir == 2) For (j, 1, n) solve(j, m, len, dir);
        else For (j, 1, n) solve(j, 1, len, dir);
    }
    printf("%d", ans);
    
    return 0;
}
