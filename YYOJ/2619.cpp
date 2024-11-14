#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e3 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
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

int n, m, dis[N], cnt[N], tot, _2[N], ans;
vector<int > es[N];

inline void bfs(int rt) {
    For (i, 1, n) dis[i] = n;
    dis[rt] = 0;
    queue<int > q; q.push(rt);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &v : es[u]) if (cmin(dis[v], dis[u] + 1)) q.push(v);
    }
}

int main() {
    _2[0] = 1; For (i, 1, N - 1) _2[i] = mo(_2[i - 1] << 1);
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (i, 1, n) {
        bfs(i);
        tot = 0;
        For (j, 1, n) cnt[dis[j]]++;
        For (j, 0, n - 1) while (cnt[j]) dis[++tot] = j, cnt[j]--;
        For (j, 1, n) add(ans, ml(dis[j], _2[n - j]));
    }
    printf("%d", ans);

    return 0;
}
