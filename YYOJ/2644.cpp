#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, M = 1e5 + 5;
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

const char mp[4] = {'N', 'S', 'W', 'E'};
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int n, m, len, dis[N][N], Dis[N][N];
char g[N][N], s[M];
vector<array<int, 2 > > q[M];

inline void init(int X, int Y) {
    memset(Dis, 31, sizeof Dis);
    queue<array<int, 2 > > q;
    Dis[X][Y] = 0; q.push({X, Y});
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        For (k, 0, 3) {
            int a = x + dx[k], b = y + dy[k];
            if (g[a][b] ^ '#' && cmin(Dis[a][b], Dis[x][y] + 1)) q.push({a, b});
        }
    }
}

int main() {
    io >> m >> n;
    For (i, 1, n) scanf("%s", g[i] + 1);
    scanf("%s", s + 1);
    len = strlen(s + 1);
    memset(dis, 31, sizeof dis);
    For (i, 1, n) For (j, 1, m) if (g[i][j] == 'S') q[0].pb({i, j}), dis[i][j] = 0, init(i, j);
    For (i, 1, len) {
        For (k, 0, 3) if (mp[k] ^ s[i]) {
            for (auto &[x, y] : q[i - 1]) {
                int a = x + dx[k], b = y + dy[k];
                if (g[a][b] ^ '#' && cmin(dis[a][b], i) && Dis[a][b] == i) q[i].pb({a, b});
            }
        }
    }
    for (auto &[x, y] : q[len]) g[x][y] = '!';
    For (i, 1, n) printf("%s\n", g[i] + 1);

    return 0;
}
