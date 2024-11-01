#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e5 + 5;

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

int n, m, U[N], V[N], vis[N], f[N][2], ans[N];
unordered_map<int, vector<int > > es[N];

inline void dfs0(int u, int pre) {
    vis[u] = 1;
    for (auto &[v, a] : es[u]) if (v ^ pre) dfs0(v, u);
    if (pre) {
        vector<array<int, 2 > > q;
        for (auto &[v, a] : es[u]) if (v ^ pre) {
            int n = a.size() - 1;
            For (i, 0, n) q.pb({a[i], f[a[i]][0] - (i<n? f[a[i + 1]][0]: 0)});
        }
        sort(q.begin(), q.end());
        vector<int > a = es[u][pre];
        int x = 1;
        while (!a.empty() || !q.empty()) {
            if (!a.empty() && (q.empty() || a.back() > q.back()[0])) f[a.back()][0] += x, a.pop_back();
            else x += q.back()[1], q.pop_back();
        }
    }
}

inline void dfs1(int u, int pre) {
    vector<array<int, 2 > > q;
    for (auto &[v, a] : es[u]) if (v ^ pre) {
        int n = a.size() - 1;
        For (i, 0, n) q.pb({a[i], f[a[i]][0] - (i<n? f[a[i + 1]][0]: 0)});
    }
    sort(q.begin(), q.end());
    vector<int > a; if (pre) a = es[u][pre];
    int x = 1, y = 0;
    while (!a.empty() || !q.empty()) {
        if (!a.empty() && (q.empty() || a.back() > q.back()[0])) y = f[a.back()][1], a.pop_back();
        else x += q.back()[1], f[q.back()[0]][1] = x + y - f[q.back()[0]][0], q.pop_back();
    }
    for (auto &[v, a] : es[u]) if (v ^ pre) dfs1(v, u);
    for (auto &[v, a] : es[u]) ans[u] += f[a[0]][v==pre];
}

int main() {
    io >> n >> m;
    For (i, 1, n - 1) io >> U[i] >> V[i];
    int x;
    For (i, 1, m) io >> x, es[U[x]][V[x]].pb(i), es[V[x]][U[x]].pb(i);
    For (i, 1, n) if (!vis[i]) dfs0(i, 0), dfs1(i, 0);
    For (i, 1, n) printf("%d ", ans[i] + 1);

    return 0;
}
