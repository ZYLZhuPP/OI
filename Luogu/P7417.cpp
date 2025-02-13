#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, inf = 1e9;
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

int T, n, m, dis[N][2], f[N], cnt[N], ans;
vector<int > es[N], pt[N * 3];
bool vis[N];

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n >> m;
        For (i, 1, n) es[i].resize(0);
        For (i, 1, 3 * n) pt[i].resize(0);
        int u, v; 
        For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
        queue<array<int, 2 > > q;
        For (i, 1, n) dis[i][0] = dis[i][1] = inf;
        dis[1][0] = 0; q.push({1, 0});
        while (!q.empty()) {
            int u = q.front()[0], k = q.front()[1]; q.pop();
            for (auto &v: es[u]) if (cmin(dis[v][!k], dis[u][k] + 1)) q.push({v, !k});
        }
        if (dis[1][1] == inf) { printf("%d\n", n - 1); continue; }
        For (i, 1, n) pt[dis[i][0] + dis[i][1]].pb(min(dis[i][0], dis[i][1]));
        for (int d = 1; d <= 3 * n - 2; d += 2) if (!pt[d].empty()) {
            if (d > 1) for (auto &x : pt[d - 2]) vis[x] = 1;
            sort(pt[d].begin(), pt[d].end());
            for (auto &x : pt[d]) ++cnt[x];
            pt[d].erase(unique(pt[d].begin(), pt[d].end()), pt[d].end());
            for (auto &x : pt[d]) {
                int y = d - x;
                if (!x) ans += y == 1;
                else if (x + 1 == y) {
                    int t = min(cnt[x], f[x - 1]);
                    if (vis[x - 1]) ans += f[x - 1] + cnt[x] - t + (t + 1) / 2;
                    else ans += max(cnt[x], f[x - 1]) + (cnt[x] + 1) / 2; 
                } else if (vis[x - 1]) {
                    f[x] = min(f[x - 1], cnt[x]);
                    if (cnt[x + 1]) ans += max(f[x - 1], cnt[x]);
                    else ans += f[x - 1] + cnt[x];
                } else {
                    ans += max(cnt[x], f[x - 1]);
                    f[x] = cnt[x];
                }
            }
            for (auto &x : pt[d]) f[x] = cnt[x] = 0;
            if (d > 1) for (auto &x : pt[d - 2]) vis[x] = 0;
        }
        printf("%d\n", ans);
    }

    return 0;
}
