#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int n, q, U[N], fa[N], pa[N], cnt[N], ans[N];
char op[N][3];
vector<int > es[N];

inline int find(int x) { return pa[x]^x? pa[x] = find(pa[x]): x; }

inline void dfs0(int u, int pre) {
    pa[u] = cnt[u]? u: pre; fa[u] = pre;
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u);
}

int main() {
    io >> n >> q; cnt[1] = 1;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    For (i, 1, q) {
        scanf("%s", op[i]);
        io >> U[i];
        if (op[i][0] == 'C') cnt[U[i]]++;
    }
    dfs0(1, 0);
    rFor (i, q, 1) {
        if (op[i][0] == 'C') { if (!--cnt[U[i]]) pa[U[i]] = fa[U[i]]; }
        else ans[i] = find(U[i]);
    }
    For (i, 1, q) if (op[i][0] == 'Q') printf("%d\n", ans[i]);

    return 0;
}
