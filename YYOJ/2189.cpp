#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 305, M = 1e6;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
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

const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m, x, y, X, Y, vis[N][N], f[4][N][N], s[4][N][N], S[N], T[N], ans, cnt[M << 1], L[N][N];
char g[N][N];
vector<array<int, 4 > > no;

inline void dfs(int i, int j) {
    cmin(x, i); cmin(y, j); cmax(X, i); cmax(Y, j);
    vis[i][j] = 1;
    For (k, 0, 3) {
        int a = i + dx[k], b = j + dy[k];
        if (a && a <= n && b && b <= m && !vis[a][b] && g[a][b] == g[i][j]) dfs(a, b);
    }
}

inline void upd(int x, int d) { cnt[S[x] + T[x + 1] + M] += d; }
inline int query(int x) { return cnt[S[x] - 1 + M]; }

int main() {
    io >> n >> m;
    For (i, 1, n) scanf("%s", g[i] + 1);
    For (i, 1, n) For (j, 1, m) if (g[i][j] == '1') {
        f[0][i][j] = 1;
        f[1][i][j] = i>1 && g[i - 1][j]=='1';
        f[2][i][j] = j>1 && g[i][j - 1]=='1';
        f[3][i][j] = f[1][i][j] && f[2][i][j] && f[1][i][j - 1] && f[2][i - 1][j];
    }
    For (i, 1, n) For (j, 1, m) For (k, 0, 3) s[k][i][j] = s[k][i][j - 1] + f[k][i][j];
    For (i, 1, n) For (j, 1, m) if (g[i][j] == '0' && !vis[i][j]) {
        x = X = i; y = Y = j;
        dfs(i, j);
        if (x > 1 && X < n && y > 1 && Y < m) no.pb({x, X, y, Y});
    }
    For (x0, 1, n) {
        memset(S, 0, sizeof S);
        memset(T, 0, sizeof T);
        memset(L, 0, sizeof L);
        for (auto &[x, X, y, Y] : no) if (x > x0) cmax(L[X + 1][Y + 1], y - 1);
        For (i, 1, n) For (j, 1, m) cmax(L[i][j], max(L[i - 1][j], L[i][j - 1]));
        For (i, x0, n) {
            For (j, 1, m) {
                S[j] += s[0][i][j] - s[2][i][j]; T[j] -= f[2][i][j];
                if (i > x0) S[j] += s[3][i][j] - s[1][i][j], T[j] += f[3][i][j];
            }
            int l = 0; upd(0, 1);
            For (j, 1, m) {
                while (L[i][j] > l) upd(l++, -1);
                ans += query(j);
                upd(j, 1);
            }
            while (l <= m) upd(l++, -1);
        }
    }
    printf("%d", ans);

    return 0;
}
