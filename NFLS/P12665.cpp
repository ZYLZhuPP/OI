#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, m, d[N], dfn[N], low[N], tim, del[N], stk[N], top;
vector<int > es[N], ans;

inline void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : es[u]) if (!del[v]) {
        if (!dfn[v]) {
            Tarjan(v); cmin(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                int d = 0, v1 = stk[top] + n;
                do ans.pb(stk[top] + d), d = n - d;
                while (stk[top--] ^ v);
                ans.pb(v1);
                ans.pb(v + d);
            }
        } else cmin(low[u], dfn[v]);
    }
}

int main() {
    freopen("dziady.in", "r", stdin);
    freopen("dziady.out", "w", stdout);
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u), d[u]++, d[v]++;
    queue<int > q;
    For (i, 1, n) if (d[i] & 1) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (~d[u] & 1) continue;
        for (auto &v : es[u]) if (!del[v]) if (--d[v] & 1) q.push(v);
        d[u] = 0; del[u] = 1; ans.pb(u);
    }
    ans.pb(0);
    For (i, 1, n) if (del[i]) ans.pb(i);
    else if (!dfn[i]) Tarjan(i), ans.pb(i);
    printf("0 %d\n", (int)ans.size());
    for (auto &u : ans) if (u) printf("1 %d\n", u); else puts("2");

    fclose(stdin); fclose(stdout);
    return 0;
}
