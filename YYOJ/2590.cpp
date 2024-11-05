#include<bits/stdc++.h>
using namespace std;

#define nd second   
#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e18;
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

int n, m, V[41], U[41], W[41], vis[10];
vector<array<int, 2 > > es[10];
ll K, L, f[512][512][41], g[512][512][41], dis[10][10], d[41][41];
vector<array<int, 3 > > F, G;

inline void Dij(int rt, ll dis[]) {
    For (i, 1, n) dis[i] = INF, vis[i] = 0;
    priority_queue<pair<ll, int > > q;
    dis[rt] = 0; q.push({0, rt});
    while (!q.empty()) {
        int u = q.top().nd; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w] : es[u]) if (!vis[v] && cmin(dis[v], dis[u] + w)) q.push({-dis[v], v});
    }
}

inline bool get(int x, int k) { return x >> (k - 1) & 1; }

int main() {
    io >> n >> m >> K >> L;
    For (i, 1, m) io >> U[i] >> V[i] >> W[i], es[U[i]].pb({V[i], W[i]}), es[V[i]].pb({U[i], W[i]});
    For (i, 1, m) if (U[i] < V[i]) swap(U[i], V[i]);
    For (i, 1, n) Dij(i, dis[i]);
    For (i, 1, m) For (j, 1, m) d[i][j] = K / (min(min(dis[U[i]][U[j]], dis[U[i]][V[j]]), min(dis[V[i]][U[j]], dis[V[i]][V[j]])) + 1);
    memset(f, 31, sizeof f); memset(g, 31, sizeof g);
    f[0][0][0] = 0; F.pb({0, 0, 0});
    For (i, 1, m) {
        for (auto &[a, b, c] : F) g[a][b][c] = f[a][b][c];
        for (auto &[a, b, c] : F) f[a][b][c] = INF;
        swap(G, F); F.resize(0);
        for (auto &[a, b, c] : G) {
            For (j, c + 1, m) if (!get(a, U[j]) || !get(a, V[j]) || get(b, U[j]) != get(b, V[j])) {
                ll x = g[a][b][c] + d[c][j];
                if (x > L) continue;
                int a_ = a | (1 << (U[j] - 1)) | (1 << (V[j] - 1));
                if (get(a, U[j]) && get(a, V[j])) {
                    if (f[a][b][j] >= INF) F.pb({a, b, j});
                    cmin(f[a][b][j], x);
                } else if (get(a, U[j])) {
                    int b_ = b | (!get(b, U[j]) << (V[j] - 1));
                    if (f[a_][b_][j] >= INF) F.pb({a_, b_, j});
                    cmin(f[a_][b_][j], x);
                } else if (get(a, V[j])) {
                    int b_ = b | (!get(b, V[j]) << (U[j] - 1));
                    if (f[a_][b_][j] >= INF) F.pb({a_, b_, j});
                    cmin(f[a_][b_][j], x);
                } else {
                    int b_ = b | (1 << (U[j] - 1));
                    if (f[a_][b_][j] >= INF) F.pb({a_, b_, j});
                    cmin(f[a_][b_][j], x);
                }
            }
        }
        if (F.empty()) {
            printf("%d\n", i - 1);
            ll x = INF;
            for (auto &[a, b, c] : G) cmin(x, g[a][b][c]);
            printf("%lld", x);
            return 0;
        }
    }
    printf("%d\n", m);
    ll x = INF;
    for (auto &[a, b, c] : F) cmin(x, f[a][b][c]);
    printf("%lld", x);

    return 0;
}
