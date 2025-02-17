#include<bits/stdc++.h>
using namespace std;

#define pb push_back
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

set<int > a[N];
int n, m, dfn[N], dfn_[N], pt[N], tim;
vector<int > T[N];

struct BIT {
    ll o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const ll &d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline ll query(int x) { ll r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
} A, B;

inline void upd(int x, int d) { A.upd(dfn[x], d); A.upd(dfn_[x] + 1, -d); B.upd(dfn[x], 1ll * (dfn_[x] - dfn[x] + 1) * d); }
inline ll query(int x) { return A.query(dfn[x]) * (dfn_[x] - dfn[x] + 1) + B.query(dfn_[x]) - B.query(dfn[x]); }

void dfs(int u) {
    pt[dfn[u] = ++tim] = u;
    for (auto &v : T[u]) if (!dfn[v]) dfs(v);
    dfn_[u] = tim;
}

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, T[u].pb(v), T[v].pb(u);
    dfs(1);
    while (m--) {
        int op, x, c;
        io >> op;
        if (op == 1) {
            io >> x >> c;
            auto it = a[c].upper_bound(dfn[x]);
            if (it != a[c].begin() && dfn_[pt[*prev(it)]] >= dfn_[x]) continue;
            while (it != a[c].end() && *it <= dfn_[x]) upd(pt[*it], -1), a[c].erase(it++);
            upd(x, 1), a[c].insert(dfn[x]);
        } else io >> x, printf("%lld\n", query(x));
    }

    return 0;
}
