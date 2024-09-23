#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;

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

int n, m;
vector<int > G[N];

namespace Blossom {
    int match[N], pre[N], tp[N], fa[N], co[N], color;
    queue<int > q;
    inline int lca(int u, int v) {
        color++;
        while (co[u] ^ color) {
            if (u) co[u] = color, u = fa[pre[match[u]]];
            swap(u, v);
        }
        return u;
    }
    inline void blossom(int u, int v, int f) {
        while (fa[u] ^ f) {
            pre[u] = v;
            v = match[u];
            if (tp[v] == 1) tp[v] = 0, q.push(v);
            fa[u] = fa[v] = fa[f];
            u = pre[v];
        }
    }
    inline bool bfs(int rt) {
        For (i, 1, n) fa[i] = i, tp[i] = -1;
        q = queue<int >();
        tp[rt] = 0; q.push(rt);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &v : G[u])
                if (!~tp[v]) {
                    pre[v] = u; tp[v] = 1;
                    if (!match[v]) {
                        for (int x = u, y = v; y; x = pre[y]) match[y] = x, swap(match[x], y);
                        return 1;
                    }
                    tp[match[v]] = 0;
                    q.push(match[v]);
                } else if (!tp[v] && fa[u] ^ fa[v]) {
                    int f = lca(fa[u], fa[v]);
                    blossom(u, v, f);
                    blossom(v, u, f);
                }
        }
        return 0;
    }
    inline int Match() {
        int res = 0;
        For (i, 1, n) if (!match[i]) res += bfs(i);
        return res;
    }
}
using namespace Blossom;

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, G[u].pb(v), G[v].pb(u);
    printf("%d\n", Match());
    For (i, 1, n) printf("%d ", match[i]);

    return 0;
}
