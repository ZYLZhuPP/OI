#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, lgW = 31;

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
	inline bool operator ~ () {return ~c;}
} io;

struct Edge {
    int to, w;
};
vector<Edge > es[N];

int n, u, v, w;
int ch[N * lgW][2], tot, cnt[N * lgW], s[N];
int dfn[N], siz[N], tim, rdfn[N];

void dfs(int u, int pre) {
    dfn[u] = ++tim; rdfn[tim] = u; siz[u] = 1;
    for (auto &e : es[u]) if (e.to ^ pre) {
        s[e.to] = s[u] ^ e.w;
        dfs(e.to, u);
        siz[u] += siz[e.to];
    }
}

void add(int x, int d) {
    int u = 0;
    for (int i = 30; i >= 0; --i) {
        int c = x >> i & 1;
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
        cnt[u] += d;
    }
}

int get(int x) {
    int res = 0, u = 0;
    for (int i = 30; i >= 0; --i) {
        int c = x >> i & 1;
        if (!cnt[ch[u][c]]) {
            res ^= 1 << i;
            u = ch[u][!c];
        } else u = ch[u][c];
    }
    return res;
}

int main() {
    io >> n;
    For (i, 2, n) {
        io >> u >> v >> w;
        es[u].push_back({v, w});
        es[v].push_back({u, w});
    }
    dfs(1, 0);

    For (i, 1, n) add(s[i], 1);

    For (i, 2, n) {
        int ans = 1 << 30;
        For (j, dfn[i], dfn[i] + siz[i] - 1) add(s[rdfn[j]], -1);
        For (j, dfn[i], dfn[i] + siz[i] - 1) ans = min(ans, get(s[rdfn[j]]));
        For (j, dfn[i], dfn[i] + siz[i] - 1) add(s[rdfn[j]], 1);
        printf("%d\n", ans);
    }
    return 0;
}
