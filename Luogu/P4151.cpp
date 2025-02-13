#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 5e4 + 5, S = 64;

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

struct Edge { int to; ll w; };
vector<Edge > es[N];
int n, m, vis[N];
ll val[N], ans;

namespace Basis {
    ll o[S];
    inline void ins(ll v) {
        rFor (i, S - 1, 0) if (v >> i & 1) {
            if (!o[i]) { o[i] = v; break; }
            v ^= o[i];
        }
    }
}
using namespace Basis;

void dfs(int u) {
    vis[u] = 1;
    for (auto &[v, w] : es[u]) if (!vis[v]) {
        val[v] = val[u] ^ w;
        dfs(v);
    } else ins(val[u] ^ val[v] ^ w);
}

int main() {
    io >> n >> m;
    int u, v; ll w;
    For (i, 1, m) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
    dfs(1);
    ans = val[n];
    rFor (i, S - 1, 0) if (!(ans >> i & 1)) ans ^= o[i];
    printf("%lld", ans);

    return 0;
}
