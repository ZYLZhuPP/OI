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

int n, fa[N], w[N], d[N], dep[N], f[N], vis[N];
vector<int > es[N];

void dfs(int u) { dep[u] = dep[fa[u]] + 1; for (auto &v : es[u]) dfs(v); }
void ins(int u) {
    f[u]++;
    vis[u] = 1;
    for (u = fa[u]; u && !vis[u]; u = fa[u]) ++f[u];
    vis[u] = 0;
}

int main() {
    io >> n;
    For (i, 1, n) io >> w[i] >> fa[i], es[fa[i]].pb(i), d[i] = i;
    dfs(1);
    sort(d + 1, d + n + 1, [&](int a, int b) { return w[a]^w[b]? w[a]<w[b]: dep[a]<dep[b]; });
    For (i, 1, n) ins(d[i]);
    printf("%d", f[1]);

    return 0;
}
