#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
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

int n, m, K, dis[N][N], id[N];
vector<int > es[N], pos[N];
ll w[N], ans;

inline void bfs(int rt, int dis[]) {
    queue<int > q; dis[rt] = 0; q.push(rt);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &v : es[u]) if (cmin(dis[v], dis[u] + 1)) q.push(v);
    }
}

int main() {
    memset(dis, 31, sizeof dis);
    io >> n >> m >> K; K++;
    For (i, 2, n) io >> w[i], id[i] = i;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
    sort(id + 2, id + n + 1, [&](const int &x, const int &y) { return w[x]>w[y]; });
    For (i, 1, n) bfs(i, dis[i]);
    For (u, 2, n) {
        For (i, 2, n) {
            int v = id[i];
            if (u == v || dis[1][v] > K || dis[u][v] > K) continue;
            pos[u].pb(v);
            if (pos[u].size() == 3) break;
        }
    }
    For (u, 2, n) For (v, u + 1, n) if (dis[u][v] <= K) {
        for (auto &x : pos[u]) for (auto &y : pos[v]) if (x ^ v && y ^ u && x ^ y) cmax(ans, w[u] + w[v] + w[x] + w[y]);
    }
    printf("%lld", ans);

    return 0;
}
