#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e6 + 5;

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
	inline bool operator ~() {return ~c;}
} io;

int n, m, q, u, v, l, r, lg[N], f[22][N], f1[N << 1], f2[N << 1], ans;
bool vis[N << 1];
vector<int > es[N << 1];

int find(int *fa, int u) { return u^fa[u]? fa[u]=find(fa, fa[u]): u; }

void dfs(int u, int pre) {
    vis[u] = 1;
    if (u <= n) {
        if (u > 1 && vis[u - 1]) f[1][u - 1] = find(f2, u - 1) - n;
        if (u < n && vis[u + 1]) f[1][u] = find(f2, u + 1) - n;
    }
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u);
    f2[u] = pre;
}

int main() {
    io >> n >> m >> q;
    For (i, 1, n + m) f1[i] = f2[i] = i;
    For (i, 1, m) {
        io >> u >> v;
        int fu = find(f1, u), fv = find(f1, v);
        if (fu ^ fv) {
            f1[fu] = f1[fv] = n + i;
            es[n + i].push_back(fu);
            es[n + i].push_back(fv);
        }
    }
    dfs(find(f1, 1), 0);

    lg[1] = 0;
    For (i, 2, n) lg[i] = lg[i >> 1] + 1;
    For (i, 2, lg[n]) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
    }

    For (i, 1, q) {
        io >> l >> r;
        if (l > r) swap(l, r);
        int j = lg[r - l + 1];
        ans ^= max(f[j][l], f[j][r - (1 << j) + 1]);
    }

    printf("%d", ans);

    return 0;
}
