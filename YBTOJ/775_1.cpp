#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef long double lf;
const int N = 1e5 + 5;
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

int n, vis[N], rt;
//vector<int > nxt;
ll ans;
lf sum[N];

struct Graph {
    struct Edge { int to; ll w; };
    vector<Edge > es[N];
    ll dis[N];
    void init() { int u, v; ll w; For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w}); }
    void dfs(int u, int pre) {
        for (auto &e : es[u]) if (e.to ^ pre) {
            dis[e.to] = dis[u] + e.w;
            dfs(e.to, u);
        }
    }
} G[3];

int solve(int rt) {
    vis[rt] = 1;
    ll mx = 0, w;
    For (i, 0, 2) G[i].dis[rt] = 0, G[i].dfs(rt, 0);
    For (i, 1, n) {
        w = G[0].dis[i] + G[1].dis[i] + G[2].dis[i];
        sum[i] += w / n;
        if (rand() % 10 && cmax(mx, w)) rt = i;
    }
    cmax(ans, mx);
    return rt;
}

int main() {
    int ST = clock();
    srand(time(0));
    io >> n;
    For (i, 0, 2) G[i].init();
    if (n <= 3100) For (i, 1, n) solve(i);
    else {
        solve(1); solve(n);
        while (clock() - ST <= 3000000) {
            while (vis[rt = rand() % n + 1]);
            //rt = nxt[rand() % nxt.size()];
            //nxt.resize(0);
            For (i, 1, 10) {
                if (vis[rt]) break;
                rt = solve(rt);
            }
            //solve(rt);
        }
        while (clock() - ST <= 3800000) {
            lf mx = 0;
            For (i, 1, n) if (!vis[i] && rand() % 3 && cmax(mx, sum[i])) rt = i;
            //while (vis[rt = rand() % n + 1]);
            //rt = nxt[rand() % nxt.size()];
            //nxt.resize(0);
            For (i, 1, 8) {
                if (vis[rt]) break;
                rt = solve(rt);
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
