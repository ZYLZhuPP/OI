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
	inline bool operator ~ () { return ~c; }
} io;

int T, n, m, dfn[N], co[N], in[N], tim, pt[N], tot, vis[N], cnt;
vector<int > es[N];

inline int Tarjan(int u, int pre) {
    dfn[u] = ++tim;
    for (auto &v : es[u]) if (v ^ pre) {
        if (dfn[v]) return pt[++tot] = u, v;
        else {
            int x = Tarjan(v, u);
            if (x) return pt[++tot] = u, x^u? x: 0;
        }
    }
    return 0;
}

inline void dfs(int u, int pre) {
    co[u] = 1;
    for (auto &v : es[u]) if (!in[v] && !co[v]) dfs(v, u);
}

inline void dfs0(int u, int pre) {
    vis[u] = 1; cnt++;
    for (auto &v : es[u]) if (!vis[v]) dfs0(v, u);
}

int main() {
    io >> T;
    while (T--) {
        int flag = 1; cnt = tot = tim = 0;
        io >> n >> m;
        For (i, 1, n) dfn[i] = co[i] = in[i] = vis[i] = 0, es[i].resize(0);
        int u, v;
        For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
        dfs0(1, 0);
        if (cnt < n) flag = 0;
        Tarjan(1, 0);
        if (!tot) flag = 0;
        if (!flag) { puts("-1"); continue; }
        For (i, 1, tot) in[pt[i]] = 1;
        dfs(pt[1], 0);
        For (i, 1, n) putchar(co[i]? 'B': 'W');
        puts("");
    }

    return 0;
}
