#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e5 + 5, inf = 1e9;
template<class C > inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    bool operator ~ () const { return ~c; }
} io;

int T, n, m, ans, dis[N], d[N];
map<int, deque<array<int, 3 > > > op;
vector<array<int, 2 > > es[N];
priority_queue<array<int, 2> > Q;

inline void add(int x, int u, int v, int w) {
    es[u].pb({v, w});
    dis[u] = dis[u]>=x? dis[u]: x + ((x&1)^(dis[u]&1));
    if (dis[u] >= w) return;
    Q.push({-dis[u], u});
}

int main() {
    io >> T;
    while (T--) {
        ans = inf;
        memset(dis, 63, sizeof dis);
        op.clear();
        io >> n >> m;
        For (i, 1, m) {
            int u, v, l, r;
            io >> u >> v >> l >> r;
            if (!l && (u == 1 || v == 1)) dis[1] = 0;
            op[l].push_front({u, v, r});
            op[r].push_back({u, v, -r});
        }
        for (auto &[x, q] : op) {
            if (ans <= x) break;
            for (auto &[u, v, w] : q) {
                if (w > 0){
                    d[u]++; d[v]++;
                    add(x, u, v + n, w); add(x, v + n, u, w);
                    add(x, v, u + n, w); add(x, u + n, v, w);
                } else {
                    w = -w;
                    if (!--d[u]) dis[u] = dis[u + n] = inf;
                    if (!--d[v]) dis[v] = dis[v + n] = inf;
                }
            }
            while (!Q.empty()) {
                int u = Q.top()[1]; Q.pop();
                if ((u - 1) % n + 1 == n) cmin(ans, dis[u]);
                for (auto &[v, w] : es[u]) if (dis[u] < w && cmin(dis[v], dis[u] + 1)) Q.push({-dis[v], v});
            }
        }
        printf("%d\n", ans<inf? ans: -1);
        For (i, 1, 2 * n) es[i].clear();
    }

    return 0;
}
