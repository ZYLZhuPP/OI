#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5;

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

int n, m, C, L, K;
unordered_map<int, int > dis[N];
vector<array<int, 2 > > es[N];
vector<int > ans;

int main() {
    io >> n >> m >> C >> L >> K;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    priority_queue<array<int, 3 > > q;
    For (i, 1, C) q.push({0, i, i});
    while (!q.empty()) {
        auto [d, rt, u] = q.top(); d = -d; q.pop();
        if (d > L || (int)dis[u].size() == K || dis[u].count(rt)) continue;
        dis[u][rt] = d;
        for (auto &[v, w] : es[u]) if (!dis[v].count(rt)) q.push({-(d + w), rt, v});
    }
    For (i, C + 1, n) if ((int)dis[i].size() == K) ans.pb(i);
    printf("%d\n", (int)ans.size());
    for (auto &x : ans) printf("%d\n", x);

    return 0;
}
