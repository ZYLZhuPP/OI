#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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
	inline bool operator ~ () const { return ~c; }
} io;

int T, n, m, a[N], dep[N], U[N], V[N];
vector<array<int, 2 > > es[N], ans;

inline int dfs(int u, int pre, int pid) {
    int x = 0;
    dep[u] = dep[pre] + 1;
    for (auto &[v, id] : es[u]) if (v ^ pre && dep[v] < dep[u]) {
        int y = !dep[v]? dfs(v, u, id): id;
        if (!y) continue;
        if (!x) x = y;
        else ans.pb({x, y}), x = 0;
    }
    if (x && pid) return ans.pb({x, pid}), 0;
    return pid;
}

inline void solve() {
    m = 0;
    ans.resize(0);
    unordered_map<int, vector<int > > mp;
    For (i, 1, n) mp[i - a[i]].pb(i);
    for (auto &[x, q] : mp) { m++; for (auto &u : q) U[u] = m; }
    mp.clear();
    For (i, 1, n) mp[i + a[i]].pb(i);
    for (auto &[x, q] : mp) { m++; for (auto &u : q) V[u] = m; }
    For (i, 1, m) dep[i] = 0, es[i].resize(0);
    For (i, 1, n) es[U[i]].pb({V[i], i}), es[V[i]].pb({U[i], i});
    For (i, 1, m) if (!dep[i]) dfs(i, 0, 0);
    if ((int)ans.size() < n / 2) puts("No");
    else {
        puts("Yes");
        for (auto &[u, v] : ans) printf("%d %d\n", u, v);
    }
}

int main() {
    io >> T;
    while (T--) {
        io >> n;
        For (i, 1, n) io >> a[i];
        solve();
    }

    return 0;
}
