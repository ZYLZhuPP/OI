#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;
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

int n, m, T, vis[N];
ll ans;
vector<array<int, 2 > > es[N];
priority_queue<pair<ll, int > > Q, q[N];
unordered_map<int, ll > dis[N];

int main() {
    io >> n >> m >> T;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    For (i, 1, T) io >> u, dis[u][u] = 0, Q.push({0, u}), q[u].push({0, u});
    while (!Q.empty()) {
        int i = Q.top().nd; Q.pop();
        int u = q[i].top().nd; ll d = -q[i].top().st; q[i].pop();
        if (vis[u]) {
            if (vis[u] ^ i) {
                ans = dis[vis[u]][u] + d;
                break;
            }
        } else {
            vis[u] = i;
            for (auto &[v, w] : es[u]) if (!dis[i].count(v)? dis[i][v] = d + w, 1: cmin(dis[i][v], d + w)) q[i].push({-(d + w), v});
        }
        if (!q[i].empty()) Q.push({q[i].top().st, i});
    }
    printf("%lld", ans);

    return 0;
}
