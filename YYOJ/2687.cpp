#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef array<int, 2 > P;
const int N = 1e5 + 5;
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

int n, L, T, Dis[N], dis[N], ans;
char s[N];
vector<int > es[N];
queue<int > q;
P f[N];

inline P merge(P a, P b) {
    if (!a[0]) return b;
    if (!b[0]) return a;
    if (a[0] == -1) swap(a, b);
    if (a[0] == -1) return {-1, max(a[1], b[1])};
    if (b[0] == -1) return a[1] + b[1] <= L? a: b;
    return {1, min(a[1], b[1])};
}

inline void dfs(int u, int pre) {
    f[u] = {-(s[u]&1), 0};
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u); if (f[v][0]) f[v][1]++;
        f[u] = merge(f[u], f[v]);
    }
    if (f[u][0] == -1 && (!pre || f[u][1] + dis[pre] >= L)) f[u] = {1, dis[u]}, ans++;
}

inline void solve() {
    io >> L;
    memset(dis, 31, sizeof dis);
    For (i, 1, n) if (s[i] ^ 48 && Dis[i] > L) dis[i] = 0, q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &v : es[u]) if (cmin(dis[v], dis[u] + 1)) q.push(v);
    }
    For (i, 1, n) if (s[i] ^ 48 && dis[i] > L) { puts("-1"); return; }
    ans = 0; dfs(1, 0); printf("%d\n", ans);
}

int main() {
    io >> n;
    scanf("%s", s + 1);
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    memset(Dis, 31, sizeof Dis);
    For (i, 1, n) if (s[i] ^ 49) Dis[i] = 0, q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &v : es[u]) if (cmin(Dis[v], Dis[u] + 1)) q.push(v);
    }
    io >> T;
    while (T--) solve();

    return 0;
}
