#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

struct IO {
    int c, f;
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

unordered_map<string, bool > mp;
int n, m, u, v, g[N][N], e[N][N], vis[N], id[N], d[N], ans;

void dfs(int k) {
    if (k == m) {
        For (i, 1, m) d[i] = id[i];
        sort(d + 1, d + m + 1);
        string st;
        For (i, 1, m) st += char(d[i]);
        if (!mp[st]) ans++, mp[st] = 1;
        return;
    }
    For (i, 1, n) if (!vis[i]) {
        bool ok = 1;
        For (j, 1, k) if (g[id[j]][i] ^ e[j][k + 1]) { ok = 0; break; }
        if (ok) {
            vis[i] = 1;
            id[k + 1] = i;
            dfs(k + 1);
            vis[i] = 0;
        }
    }
}

int main() {
    io >> n;
    For (i, 1, n - 1) io >> u >> v, g[u][v] = g[v][u] = 1;
    io >> m;
    For (i, 1, m - 1) io >> u >> v, e[u][v] = e[v][u] = 1;
    dfs(0);

    printf("%d", ans);
}
