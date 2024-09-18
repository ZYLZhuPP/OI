#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int n, m, fa[N][20], dep[N], p[N];
char st[N];

inline int lca(int u, int v) {
    if (dep[v] > dep[u]) swap(u, v);
    rFor (i, 19, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 19, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int main() {
    scanf("%s", st + 1);
    n = strlen(st + 1);
    int j = 0;
    For (i, 2, n) {
        while (j && st[i] ^ st[j + 1]) j = p[j];
        if (st[i] == st[j + 1]) j++;
        p[i] = j;
    }
    For (i, 1, n) {
        fa[i][0] = p[i]; dep[i] = dep[p[i]] + 1;
        For (j, 1, 19) fa[i][j] = fa[fa[i][j - 1]][j - 1];
    }
    io >> m;
    int u, v;
    while (m--) io >> u >> v, printf("%d\n", lca(p[u], p[v]));

    return 0;
}
