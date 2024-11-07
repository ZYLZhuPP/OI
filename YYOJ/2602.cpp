#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int T, n, m, a[N], pos[N], f[N], d[N], vis[N];
vector<int > G[N], R[N];

int main() {
    io >> T;
    while (T--) {
        bool flag = 1;
        io >> n >> m;
        For (i, 1, n) io >> a[i], pos[a[i]] = i;
        int u, v;
        For (i, 1, m) io >> u >> v, G[u].pb(v), R[v].pb(u);
        queue<int > q;
        For (i, 1, n) {
            d[i] = R[i].size(); f[i] = a[i];
            if (!d[i]) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &v : G[u]) {
                cmax(f[v], f[u]);
                if (!--d[v]) q.push(v);
            }
        }
        priority_queue<array<int, 2 > > Q;
        For (i, 1, n) {
            d[i] = G[i].size();
            if (!d[i]) Q.push({f[i], i});
        }
        rFor (i, n, 1) {
            int u;
            if (pos[i]) {
                u = pos[i];
                if (d[u]) { puts("-1"); flag = 0; break; }
                vis[u] = 1;
            } else {
                while (!Q.empty() && (vis[Q.top()[1]] || a[Q.top()[1]])) Q.pop();
                if (Q.empty()) { puts("-1"); flag = 0; break; }
                u = Q.top()[1]; Q.pop();
            }
            a[u] = i;
            for (auto &v : R[u]) if (!--d[v]) Q.push({f[v], v});
        }
        if (flag) For (i, 1, n) printf("%d%c", a[i], " \n"[i==n]);
        For (i, 1, n) pos[i] = vis[i] = 0, G[i].resize(0), R[i].resize(0);
    }

    return 0;
}
