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

int n, q, m, B, a[N], sz[N], f[N], g[520][520], on[N], id[N];
vector<int > es[N], big;

int main() {
    io >> n >> q >> m; B = sqrt(n);
    For (i, 1, n) {
        io >> a[i];
        if (a[i] == a[i - 1]) {
            i--; n--;
            continue;
        }
        sz[a[i]]++;
    }
    a[n + 1] = 0;
    For (i, 0, n) es[a[i]].pb(a[i + 1]), es[a[i + 1]].pb(a[i]);
    For (i, 0, m) if (es[i].size() > B) id[i] = big.size(), big.pb(i);
    for (auto &u : big) for (auto &v : es[u]) if (es[v].size() > B) g[id[u]][id[v]]++;
    int V = 0, E = 0, u;
    while (q--) {
        io >> u;
        V += (on[u]? -1: 1) * sz[u];
        if (es[u].size() <= B) {
            for (auto &v : es[u]) {
                E += (!on[u] && on[v]) - (on[u] && on[v]);
                if (es[v].size() > B) f[v] += on[u]? -1: 1;
            }
        } else {
            E += (on[u]? -1: 1) * f[u];
            for (auto &v : big) E += ((!on[u] && on[v]) - (on[u] && on[v])) * g[id[u]][id[v]];
        }
        printf("%d\n", V - E);
        on[u] ^= 1;
    }

    return 0;
}
