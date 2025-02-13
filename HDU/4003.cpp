#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e4 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, rt, m, ans, f[N][11];
vector<pair<int, int > > T[N];

inline void dfs(int u, int pre) {
    for (auto &[v, w] : T[u]) if (v ^ pre) {
        dfs(v, u);
        rFor (i, m, 0) {
            f[u][i] += f[v][0] + 2 * w;
            For (j, 1, i) cmin(f[u][i], f[u][i - j] + f[v][j] + j * w);
        }
    }
}

int main() {
    while (~(io >> n >> rt >> m)) {
        memset(f, 0, sizeof f);
        int u, v, w;
        For (i, 1, n - 1) io >> u >> v >> w, T[u].pb({v, w}), T[v].pb({u, w});
        dfs(rt, 0);
        printf("%d\n", f[rt][m]);
        For (i, 1, n) T[i].resize(0);
    }

    return 0;
}
