#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

struct IO {
    char c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m;
vector<int > es[N];
int dep[N], c[N], f[N][25];

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    
    for (int i = 20; i >= 0; i--)
        if (dep[f[u][i]] >= dep[v])
            u = f[u][i];
    if (u == v) return u;
    
    for (int i = 20; i >= 0; i--)
        if (f[u][i] ^ f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}

void dfs(int u, int pre) {
    dep[u] = dep[pre] + 1;
    
    f[u][0] = pre;
    for (int i = 1; (1 << i) <= dep[u]; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];
    
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
    }
}

void Dfs(int u, int pre) {
    for (auto &v : es[u]) if (v ^ pre) {
        Dfs(v, u);
        c[u] += c[v];
    }
}

int main() {
    io >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        io >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
    }
    
    dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        int u, v;
        io >> u >> v;
        
        c[u]++, c[v]++;
        c[lca(u, v)] -= 2;
    }
    Dfs(1, 0);
    
    long long ans = 0;
    for (int i = 2; i <= n; i++)
        if (!c[i]) ans += m;
        else if (c[i] == 1) ans++;
    
    printf("%lld", ans);
    return 0;
}

