#pragma GCC optimize(3)
#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 405;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
const char mp[5] = "UDLR";
int n, m, I, J, II, JJ, X[3], Y[3], D, f[3], ok[4][4], tot;
bool vis[N][N], g[N][N];
char s[N][N];

inline bool go(int i, int &x, int &y, int k) {
    printf("%d %c\n", i, mp[k]);
    fflush(stdout);
    int d; io >> d;
    if (d ^ D) {
        x += dx[k], y += dy[k];
        D = d;
        return 1;
    }
    return 0;
}

inline void dfs0(int x, int y) {
    if (vis[x][y] || D == 1) return;
    vis[x][y] = 1;
    For (k, 0, 3) if (!vis[x + dx[k]][y + dy[k]] && go(1, x, y, k)) {
        dfs0(x, y);
        if (D == 1) return;
        go(1, x, y, k ^ 1);
    } else vis[x + dx[k]][y + dy[k]] = 1;
}

inline void dfs(int i, int x, int y) {
    if (vis[x][y]) return;
    vis[x][y] = 1;
    cmax(II, x); cmax(JJ, y);
    For (k, 0, 3) if (!vis[x + dx[k]][y + dy[k]] && go(i, x, y, k)) {
        dfs(i, x, y);
        go(i, x, y, k ^ 1);
    } else vis[x + dx[k]][y + dy[k]] = 1;
}

inline bool dfs1(int i, int &x, int &y, int X, int Y) {
    if (x == X && y == Y) return 1;
    if (vis[x][y]) return 0;
    vis[x][y] = 1;
    For (k, 0, 3) if (g[x + dx[k]][y + dy[k]] && go(i, x, y, k)) {
        if (dfs1(i, x, y, X, Y)) return 1;
        go(i, x, y, k ^ 1);
    }
    return 0;
}

inline bool solve(int i, int &x, int &y, int k) {
    memset(vis, 0, sizeof vis);
    return dfs1(i, x, y, X[k], Y[k]);
}

inline void over() { puts("0"); fflush(stdout); }

int main() {
    io >> n >> m;
    For (i, 1, n) scanf("%s", s[i] + 1);
    For (i, 1, n) For (j, 1, m) {
        if (s[i][j] != '#') g[i][j] = 1, cmax(I, i), cmax(J, j);
        if (s[i][j] == 'x') X[++tot] = i, Y[tot] = j;
    }
    io >> D;
    dfs0(200, 200);
    int x = 0, y = 0;
    For (i, 1, 2) For (k, 0, 3) if (go(i, x, y, k)) ok[i][k] = 1, f[i] = k + 1, go(i, x, y, k ^ 1);
    if (!f[1] && !f[2]) return over(), 0;
    int t = 0;
    if (f[1]) {
        f[1]--;
        go(1, x, y, f[1]);
        For (k, 0, 3) if (go(2, x, y, k)) ok[3][k] = 1, go(2, x, y, k ^ 1);
        while (ok[2][t] == ok[3][t]) t++;
        go(1, x, y, f[1] ^ 1);
        t ^= 1;
    } else {
        f[2]--;
        go(2, x, y, f[2]);
        For (k, 0, 3) if (go(1, x, y, k)) ok[3][k] = 1, go(1, x, y, k ^ 1);
        while (ok[1][t] == ok[3][t]) t++;
        go(2, x, y, f[2] ^ 1);
    }
    memset(vis, 0, sizeof vis);
    dfs(1, 200, 200); vis[200 + dx[t]][200 + dy[t]] = 0; dfs(2, 200 + dx[t], 200 + dy[t]);
    I += 200 - II, J += 200 - JJ;
    II = I + dx[t], JJ = J + dy[t];
    (solve(1, I, J, 1) && solve(2, II, JJ, 2)) || (solve(2, II, JJ, 2) && solve(1, I, J, 1)) || (solve(1, I, J, 2) && solve(2, II, JJ, 1)) || (solve(2, II, JJ, 1) && solve(1, I, J, 2));
    over();

    return 0;
}
