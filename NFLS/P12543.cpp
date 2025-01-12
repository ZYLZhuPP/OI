#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, Mo = 998244353, inv2 = 499122177;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, q, tim, f[N][20], g[N][20], s[N], a[N];
vector<int > T[N];

inline int F(int x, int y) {
    return ml(inv2, mo(ml(s[y] - s[x - 1], s[y] - s[x - 1]) - mo(a[y] - a[x - 1])));
}

inline void dfs(int u) {
    tim++;
    for (auto &v : T[u]) dfs(tim + 1);
    f[u][0] = tim + 1;
    g[u][0] = F(u, tim);
}

inline int query(int l, int r) {
    int res = 0;
    rFor (i, 19, 0) if (f[l][i] <= r) add(res, g[l][i]), l = f[l][i];
    return mo(res + F(l, r));
}

int main() {
    freopen("dfs.in", "r", stdin);
    freopen("dfs.out", "w", stdout);
    io >> n >> q;
    For (i, 1, n) s[i] = mo(s[i - 1] + i), a[i] = (a[i - 1] + 1ll * i * i) % Mo;
    int u, v;
    For (i, 1, n - 1) {
        io >> u >> v; if (u > v) swap(u, v);
        T[u].pb(v);
    }
    dfs(1);
    f[n + 1][0] = n + 1;
    rFor (i, n + 1, 1) For (j, 1, 19) f[i][j] = f[f[i][j - 1]][j - 1], g[i][j] = mo(g[i][j - 1] + g[f[i][j - 1]][j - 1]);
    int l, r;
    while (q--) io >> l >> r, printf("%d\n", query(l, r));

    fclose(stdin); fclose(stdout);
    return 0;
}
