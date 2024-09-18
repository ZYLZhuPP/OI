#include <bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define mkp make_pair
typedef long long ll;
const int N = 3e5 + 5;
inline void cmin(int &x, const int y) { y<x? x=y: 0; }

struct IO {
	char c; int f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

vector<int> G[N], adj[N];
vector<int> R[N];
set<int> S[N];
int n, m;

struct SegTree {
    int M, k, d[N << 2];
    void upd(int p) { d[p] = min(d[p << 1], d[p << 1 | 1]); }
    void build(int n, vector<int> A) {
        k = 0, M = 1;
        while (M < n) M <<= 1, k++;
        for (int i = 1; i <= M + M; i++) d[i] = n + 1;
        for (int i = 1; i <= n; i++) d[i + M - 1] = A[i];
        for (int i = M - 1; i >= 1; i--) upd(i);
    }
    int qmin(int l, int r) {
        int res = n + 1;
        for (l += M - 1, r += M; l < r; l >>= 1, r >>= 1) {
            if (l & 1) cmin(res, d[l++]);
            if (r & 1) cmin(res, d[--r]);
        }
        return res;
    }
} T;

int dep[N], fa[N], sz[N], dfn[N], top[N], hson[N], dfc, pos[N], id[N];
void dfs1(int u, int de) {
    dep[u] = de, sz[u] = 1;
    for (int v : G[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dfs1(v, de + 1), sz[u] += sz[v];
        if (sz[v] > sz[hson[u]]) hson[u] = v;
    }
}
void dfs2(int u, int tp) {
    top[u] = tp, dfn[u] = ++dfc, id[dfc] = u;
    if (hson[u]) dfs2(hson[u], tp);
    for (int v : G[u]) {
		if (v == fa[u] || v == hson[u]) continue;
        dfs2(v, v);
    }
}
int getnode(int u, int v) {
    assert(dfn[v] >= dfn[u] && dfn[v] <= dfn[u] + sz[u] - 1);
    int de = dep[u] + 1;
    while (dep[top[v]] > de) v = fa[top[v]];
    int dis = dep[v] - de;
    return id[dfn[v] - dis];
}

struct BIT {
    int c[N];
    void clear() { memset(c, 0, sizeof(c)); }
    int lowbit(int x) { return x & (-x); }
    void Add(int x, int v) { for (int i = x; i <= n; i += lowbit(i)) c[i] += v; }
    int sum(int x) { int res = 0; for (int i = x; i; i -= lowbit(i)) res += c[i]; return res; }
    void add(int l, int r, int v) { if (l <= r) Add(r + 1, -v), Add(l, v); }
    int qval(int x) { return sum(x); }
} W;

int main() {
    io >> n >> m;
    vector<pair<int, int> > E;
    vector<int> deg(n + 1, 0);
	int u, v;
    for (int i = 1; i <= m; i++) {
        io >> u >> v;
        E.emplace_back(mkp(u, v));
        adj[u].emplace_back(v), adj[v].emplace_back(u), deg[u]++, deg[v]++;
    }

    vector<bool> vis(n + 1, 0);
    function<void(int, int)> buildtree = [&](int u, int fa) {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (!vis[v])  dep[v] = dep[u] + 1, buildtree(v, u), G[u].emplace_back(v);
            else if (dep[v] < dep[u] && v != fa) R[u].emplace_back(v);
        }
    };
    dep[1] = 1, buildtree(1, 0);
    dfs1(1, 1), dfs2(1, 1);

    vector<int> val(n + 1, n + 1);
    for (int i = 1; i <= n; i++)
        for (int j : R[i]) cmin(val[dfn[i]], dep[j]);
    T.build(n, val);

    auto Merge = [&](set<int> &A, set<int> &B) {
        if (A.size() < B.size()) swap(A, B);
        for (int x : B) A.insert(x);
        B.clear();
    };

    vector<int> mxlow(n + 1, 0), mnlow(n + 1, 0);
    function<void(int)> getlow = [&](int u) {
        for (int v : G[u]) getlow(v), Merge(S[u], S[v]);
        for (int j : R[u]) S[u].insert(dep[j]);
        S[u].erase(S[u].lower_bound(dep[u] - 1), S[u].end());
        if (S[u].size()) mxlow[u] = *--S[u].end(), mnlow[u] = *S[u].begin();
        else mxlow[u] = 0, mnlow[u] = n + 1;
    };
    getlow(1);

    W.clear();
    vector<int> cut(n + 1, 0);

    fill(vis.begin(), vis.end(), 0);
    map<pair<int, int>, bool> Ans;

    auto addres = [&](int u, int v) { Ans[mkp(u, v)] = Ans[mkp(v, u)] = 1; };
    auto getans = [&](int u) {
        if (u == 1) {
            if (G[u].size() >= 3) return;
            if (G[u].size() == 2) { for (int v : G[u]) if (sz[v] == 1) addres(u, v); }
            if (G[u].size() == 1) {
                int v = G[u][0];
                if (G[v].size() <= 1) addres(u, v);
            }
            return;
        }
        for (int v : G[u]) {
            if (mnlow[v] == mxlow[v]) vis[mnlow[v]] = 1;
            W.add(mnlow[v] + 1, mxlow[v] - 1, 1);
        }
        for (int v : G[u]) {
            if (mnlow[v] >= dep[u]) cut[u]--;
            if (cut[u] == 0) {
                bool chk = 1;
                for (int j : G[v]) if (mnlow[j] >= dep[u]) chk = 0;
                if (chk) addres(u, v);
            }
            if (mnlow[v] >= dep[u]) cut[u]++;
        }

        if (cut[u] >= 1) goto ED2;
        for (int j : R[u]) {
            int x = getnode(j, u);
            if (mnlow[x] >= dep[j]) cut[j]--;
            if (cut[j] == 0) {
                if (vis[dep[j]]) goto ED;
                if (W.qval(dep[j]) >= 1) { addres(u, j); goto ED; }
                if (j == 1) { addres(u, j); goto ED; }
                if (T.qmin(dfn[x], dfn[u] - 1) < dep[j] || T.qmin(dfn[u] + sz[u], dfn[x] + sz[x] - 1) < dep[j]) addres(u, j);
            }
        ED:
            if (mnlow[x] >= dep[j]) cut[j]++;
        }

    ED2:
        for (int v : G[u]) {
            if (mnlow[v] == mxlow[v]) vis[mnlow[v]] = 0;
            W.add(mnlow[v] + 1, mxlow[v] - 1, -1);
        }
    };

    for (int i = 1; i <= n; i++)
        for (int j : G[i]) cut[i] += (mnlow[j] >= dep[i]);
    for (int i = 1; i <= n; i++) getans(i);
    int res = 0;
    for (auto e : E) res += (Ans[mkp(e.st, e.nd)] == 0);
    cout << res << endl;

    return 0;
}
