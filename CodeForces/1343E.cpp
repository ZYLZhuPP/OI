#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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
    inline bool operator ~ () { return ~c; }
} io;

int T, n, m, A, B, C, dis[3][N], w[N];
ll s[N], ans;
vector<int > es[N];

void bfs(int S, int dis[]) {
    dis[S] = 0;
    queue<int > q; q.push(S);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &v : es[u]) if (dis[u] + 1 < dis[v]) dis[v] = dis[u] + 1, q.push(v);
    }
}

void solve() {
    io >> n >> m >> A >> B >> C;
    For (i, 1, m) io >> w[i];
    sort(w + 1, w + m + 1);
    For (i, 1, m) s[i] = s[i - 1] + w[i];
    ans = 2 * s[m];
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (i, 1, n) dis[0][i] = dis[1][i] = dis[2][i] = n;
    bfs(A, dis[0]); bfs(B, dis[1]); bfs(C, dis[2]);
    For (i, 1, n) if (dis[0][i] + dis[1][i] + dis[2][i] <= m)
        ans = min(ans, s[dis[1][i]] + s[dis[0][i] + dis[1][i] + dis[2][i]]);
    printf("%lld\n", ans);
    For (i, 1, n) es[i].resize(0);
}

int main() {
    io >> T;
    while (T--) solve();

    return 0;
}