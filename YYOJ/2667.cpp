#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
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

int n, m, dis[N], inq[N];
vector<array<int, 2 > > es[N];

inline void SPFA(int rt) {
    memset(dis, 31, sizeof dis);
    queue<int > q;
    dis[rt] = 0; q.push(rt); inq[rt] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for (auto &[v, w] : es[u]) if (cmin(dis[v], dis[u] + w) && !inq[v]) q.push(v);
    }
}

int main() {
    io >> n >> m;
    int l, r;
    For (i, 1, m) {
        io >> l >> r; l--;
        if ((r - l) & 1) return cerr << l << " " << r << endl, puts("-1"), 0;
        es[l].pb({r, (r - l) / 2}); es[r].pb({l, -(r - l) / 2});
    }
    For (i, 0, n - 1) es[i].pb({i + 1, 1}), es[i + 1].pb({i, 0});
    SPFA(0);
    For (i, 1, n) putchar(dis[i] - dis[i - 1] + '0');

    return 0;
}
