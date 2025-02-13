#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define pb push_back
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

int n, m, k, o[30], vis[N], w[N], s[N];
vector<pair<int, int > > G[N];

void dfs(int u, int pre) {
    vis[u] = 1;
    for (auto &[v, id] : G[u]) if (v ^ pre) {
        if (!vis[v]) dfs(v, u), s[u] ^= s[v], w[id] = s[v];
        else if (!w[id]) w[id] = rand(), s[u] ^= w[id], s[v] ^= w[id];
    }
}

inline bool ins(int x) {
    rFor (i, 29, 0) if (x >> i & 1) {
        if (!o[i]) return o[i] = x, 1;
        x ^= o[i];
    }
    return 0;
}

int main() {
    srand(time(0));
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, G[u].pb({v, i}), G[v].pb({u, i});
    dfs(1, 0);
    io >> k;
    while (k--) {
        memset(o, 0, sizeof o);
        int c, x; bool flag = 1;
        io >> c;
        For (i, 1, c) io >> x, flag &= ins(w[x]);
        puts(flag? "Connected": "Disconnected");
    }

    return 0;
}
