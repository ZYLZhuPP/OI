#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

int n, m, T, fa[N];
set<int > f[N], g[N];
queue<int > q;

inline int find(int x) { return x^fa[x]? fa[x] = find(fa[x]): x; }

int main() {
    io >> n >> m;
    For (i, 1, n) fa[i] = i;
    int u, v;
    For (i, 1, m) io >> u >> v, f[u].insert(v), g[v].insert(u);
    For (i, 1, n) if (f[i].empty()) q.push(i);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        fa[v] = 0;
        for (auto &u : g[v]) {
            f[u].erase(v);
            if (f[u].empty()) q.push(u);
        }
    }
    For (i, 1, n) if ((int)f[i].size() == 1) q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        int y = *f[x].begin();
        x = find(x); y = find(y);
        if (x == y) continue;
        if (g[x].size() > g[y].size()) swap(x, y);
        for (auto &z : g[x]) {
            f[z].erase(x);
            f[z].insert(y);
            g[y].insert(z);
            if ((int)f[z].size() == 1) q.push(z);
        }
        fa[x] = y;
    }
    io >> T;
    while (T--) {
        io >> u >> v;
        u = find(u); v = find(v);
        putchar(!u||!v||u==v? 'B': 'H');
    }

    return 0;   
}