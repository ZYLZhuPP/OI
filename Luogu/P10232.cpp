#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(a) a.begin(), a.end()
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;
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

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
int n, m, K, q, b[N], fa[N], dep[N], co[N], tot, len[N], ans, U[4], V[4];
vector<array<int, 2 > > a[2][N];

inline int find(int x, int y, int d) {
    int c = d & 1; if (!c) swap(x, y);
    if (a[c][x].empty()) return -1;
    array<int, 2 > p = {y, d<2? 0: K};
    auto it = lower_bound(all(a[c][x]), p);
    if (d < 2) it==a[c][x].begin()? it = a[c][x].end() - 1: it--;
    else if (it == a[c][x].end()) it = a[c][x].begin();
    return (*it)[1] << 2 | d;
}

inline int dfs(int u, int pre) {
    co[u] = tot; dep[u] = dep[pre] + 1;
    return co[fa[u]]? dep[u]: dfs(fa[u], u);
}

inline int dis(int u, int v) {
    if (co[u] ^ co[v]) return K + 1;
    int d = len[co[u]];
    return (dep[v] - dep[u] + d) % d;
}

int main() {
    io >> n >> m >> K;
    int x, y, X, Y; char op[3];
    For (i, 0, K - 1) {
        io >> x >> y; scanf("%s", op);
        b[i] = op[0]=='L'? 1: 3;
        a[0][y].pb({x, i}); a[1][x].pb({y, i});
    }
    K *= 4;
    For (i, 1, n) sort(all(a[1][i]));
    For (i, 1, m) sort(all(a[0][i]));
    For (x, 1, n) for (auto &[y, id] : a[1][x]) For (k, 0, 3) fa[id << 2 | k] = find(x, y, (k + b[id]) % 4);
    For (i, 0, K - 1) if (!co[i]) tot++, len[tot] = dfs(i, i);
    io >> q;
    while (q--) {
        ans = K + 1;
        io >> x >> y >> X >> Y;
        For (k, 0, 3) U[k] = find(x, y, k), V[k] = find(X - dx[k], Y - dy[k], k);
        For (i, 0, 3) if (~U[i]) For (j, 0, 3) if (~V[j]) cmin(ans, dis(U[i], V[j]));
        if ((x == X && a[1][x].empty()) || (y == Y && a[0][y].empty())) ans = 0;
        printf("%d\n", ans<=K? ans: -1);
    }

    return 0;
}
