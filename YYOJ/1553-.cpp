#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 5e3 + 5;
const ll Mo = 998244353;

struct IO {
	char c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

int n, u, v, ma, deg[N], siz[N];
ll f[N], inv[N];
bool g[N][N];

void init() {
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; ++i) inv[i] = (Mo - Mo / i) * inv[Mo % i] % Mo;
}

ll dfs(int u) {
    ll res = 0;
    siz[u] = 1;
    for (int v = 1; v <= n; ++v) if (g[u][v]) {
        g[u][v] = g[v][u] = 0;
        res = (res + dfs(u) * dfs(v)) % Mo;
        g[u][v] = g[v][u] = 1;
        siz[u] = siz[u] + siz[v];
        
    }
    if (siz[u] == 1) return 1;
    return res * inv[siz[u]];
}

int main() {
    io >> n;
    init();
    for (int i = 1; i < n; ++i) {
        io >> u >> v;
        g[u][v] = 1;
        deg[u]++; deg[v]++;
    }

    for (int i = 1; i <= n; ++i) ma = max(ma, deg[i]);
    if (ma == 2) {
        f[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                f[i] = (f[i] + f[j] * f[i - j]) % Mo;
            }
            f[i] = f[i] * inv[i] % Mo;
        }
        printf("%lld", f[n]);
    } else if (ma == n - 1) {
        f[1] = 1;
        for (int i = 2; i <= n; ++i) {
            f[i] = (i - 1) * f[i - 1] % Mo * inv[i] % Mo;
        }
        printf("%lld", f[n]);
    } else {
        ll ans = 0;
        for (int i = 1; i <= n; ++i) ans = (ans + dfs(i)) % Mo;
        printf("%lld", ans * inv[2] % Mo);
    }

    return 0;
}
