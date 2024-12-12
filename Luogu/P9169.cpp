#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 111, M = 1e6 + 5;

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
int ID, T, n, m, id[N][N][N], tot, vis[M], tp[M], dis[M], in[M];
char g[N][N];
int head[M], to[M << 3], nxt[M << 3], en;

inline void add(const int &u, const int &v) {
    nxt[++en] = head[u]; head[u] = en;
    to[en] = v;
}

inline int Id(const int &x, const int &y, const int &a, const int &b, const int &c, const int &d) {
    int p = a * 10 + b, q = c * 10 + d; if (p > q) swap(p, q);
    int &u = id[x * 10 + y][p][q];
    if (!u) u = ++tot;
    return u;
}

inline bool ok(const int &x, const int &y) { return x > 0 && x <= n && y > 0 && y <= m && g[x][y] ^ '#'; }

inline void bfs(int x, int y, int a, int b, int c, int d) {
    queue<array<int, 7 > > q;
    q.push({x, y, a, b, c, d, 0});
    while (!q.empty()) {
        auto [x, y, a, b, c, d, op] = q.front(); q.pop();
        if (x == 1 || (x == a && y == b) || (x == c && y == d)) continue;
        int u = Id(x, y, a, b, c, d);
        if (!op) {
            For (k, 0, 3) {
                int a_ = a + dx[k], b_ = b + dy[k];
                if (!ok(a_, b_) || (a_ == c && b_ == d)) continue;
                int v = Id(x, y, a_, b_, c, d);
                add(v, u); in[u]++;
                if (!vis[v]) vis[v] = 1, q.push({x, y, a_, b_, c, d, 1});
            }
            For (k, 0, 3) {
                int c_ = c + dx[k], d_ = d + dy[k];
                if (!ok(c_, d_) || (a == c_ && b == d_)) continue;
                int v = Id(x, y, a, b, c_, d_);
                add(v, u); in[u]++;
                if (!vis[v]) vis[v] = 1, q.push({x, y, a, b, c_, d_, 1});
            }
        } else {
            For (k, 1, 3) {
                int x_ = x + dx[k], y_ = y + dy[k];
                if (!ok(x_, y_)) continue;
                int v = Id(x_, y_, a, b, c, d);
                add(v, u); in[u]++;
                if (!vis[v]) vis[v] = 1, q.push({x_, y_, a, b, c, d, 0});
            }
        }
    }
}

inline void topo() {
    queue<int > q;
    For (i, 1, tot) if (!in[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u], v; v = to[i], i; i = nxt[i]) if (!tp[v] && (!tp[u] || !--in[v])) tp[v] = !tp[u], dis[v] = dis[u] + 1, q.push(v);
    }
}

inline void solve() {
    memset(id, 0, sizeof id);
    For (i, 1, tot) head[i] = in[i] = vis[i] = tp[i] = dis[i] = 0;
    tot = en = 0;
    io >> n >> m;
    For (i, 1, n) scanf("%s", g[i] + 1);
    int x, y, a, b, c, d; x = y = a = b = c = d = 0;
    For (i, 1, n) For (j, 1, m) {
        if (g[i][j] == 'X') x = i, y = j;
        else if (g[i][j] == 'O') { if (!a) a = i, b = j; else c = i, d = j; }
    }
    bfs(x, y, a, b, c, d);
    topo();
    int u = Id(x, y, a, b, c, d);
    if (tp[u]) printf("Red %d\n", dis[u]);
    else if (!in[u]) printf("Black %d\n", dis[u]);
    else puts("Tie");
}

int main() {
    io >> ID >> T;
    while (T--) solve();

    return 0;
}
