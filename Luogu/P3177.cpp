#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 2005;
inline void cmax(ll &x, const ll &y) { y>x? x=y: 0; }

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

int n, K, siz[N];
ll f[N][N];
vector<pair<int, int > > es[N];

void dfs(int u, int pre) {
	siz[u] = 1; f[u][0] = 0; if (K) f[u][1] = 0;
	for (auto &[v, w] : es[u]) if (v ^ pre) {
		dfs(v, u);
		For (i, 0, min(K, siz[v])) if (~f[v][i]) f[v][i] += 1ll * w * (i * (K - i) + (siz[v] - i) * (n - siz[v] - K + i));
		rFor (i, min(K, siz[u]), 0) if (~f[u][i])
			rFor (j, min(K - i, siz[v]), 0) if (~f[v][j]) 
				cmax(f[u][i + j], f[u][i] + f[v][j]);
		siz[u] += siz[v];
	}
}

int main() {
	io >> n >> K;
	int u, v, w;
	For (i, 1, n - 1) io >> u >> v >> w, es[u].pb({v, w}), es[v].pb({u, w});
	memset(f, -1, sizeof f);
	dfs(1, 0);
	printf("%lld", f[1][K]);
	
	return 0;
} 
