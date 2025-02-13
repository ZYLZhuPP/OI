#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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

int n, m, U[N], V[N], vis[N], co[N];
vector<array<int, 2 > > es[N];

inline void dfs(int u, int pre) {
    vis[u] = 1;
    for (auto &[v, id] : es[u]) if (id ^ pre) {
        if (!vis[v]) co[id] = u == U[id], dfs(v, id);
        else co[id] = u != U[id];
    }
}

int main() {
    io >> n >> m;
    For (i, 1, m) io >> U[i];
    For (i, 1, m) io >> V[i];
    For (i, 1, m) es[U[i]].pb({V[i], i}), es[V[i]].pb({U[i], i});
    For (i, 1, n) if (!vis[i]) dfs(i, 0);
    For (i, 1, m) printf("%d", co[i]);

    return 0;
}
