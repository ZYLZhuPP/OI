#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 6e5 + 5;
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

int n, m;
bool vis[N];
ll dis[N];
array<int, 2 > a[N], b[N];
vector<array<int, 2 > > es[N];

inline void Dij(int rt) {
    priority_queue<pair<ll, int > > q;
    dis[rt] = 0; q.push({0, rt});
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w] : es[u]) if (!vis[v] && cmin(dis[v], dis[u] + w)) q.push({-dis[v], v});
    }
}

int main() {
    memset(dis, 31, sizeof dis);
    io >> n >> m;
    For (i, 1, n) io >> a[i][0], a[i][1] = i;
    For (i, 1, n) io >> b[i][0], b[i][1] = i;
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
    For (i, 1, n) {
        int u = b[i][1];
        es[i + n].pb({u, b[i][0]});
        es[i + n + n].pb({u, 0});
        if (i > 1) es[i + n].pb({i + n - 1, 0});
        if (i < n) es[i + n + n].pb({i + n + n + 1, b[i + 1][0] - b[i][0]});
    }
    int p = n;
    For (i, 1, n) {
        int u = a[i][1];
        while (p && a[i][0] + b[p][0] >= m) p--;
        if (p) es[u].pb({p + n, a[i][0]});
        if (p < n) es[u].pb({p + n + n + 1, a[i][0] + b[p + 1][0] - m});
    }
    Dij(1);
    printf("%lld", dis[n]);

    return 0;
}
