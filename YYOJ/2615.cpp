#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

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

struct BIT {
    ll o[N];
    BIT() { memset(o, 0, sizeof o); }
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline ll query(int x) { ll r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
} A, B;

int n, m, dfn[N], dfn_[N], tim, son[N], dep[N];
ll ans[N];
char op[N][3];
vector<array<int, 3 > > qs[N << 1];
vector<int > es[N];

inline void dfs0(int u, int pre) {
    dfn[u] = ++tim; dep[u] = dep[pre] + 1;
    for (auto &v : es[u]) if (v ^ pre) son[u]++, dfs0(v, u);
    dfn_[u] = tim;
}

int main() {
    io >> n >> m;
    int u, v, x, d;
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    For (i, 1, n) io >> x, qs[n - dep[i]].pb({0, i, x});
    For (i, 1, m) {
        scanf("%s", op[i]);
        if (op[i][0] == '+') io >> u >> d, qs[n + i - dep[u]].pb({i, u, d});
        else io >> u, qs[n + i - dep[u]].pb({i, u, 0});
    }
    For (i, 0, n + m) {
        for (auto &[id, u, d] : qs[i]) {
            if (d) A.upd(dfn[u], d), A.upd(dfn_[u] + 1, -d), B.upd(dfn[u], d), B.upd(dfn_[u] + 1, -d);
            else ans[id] = son[u]? B.query(dfn[u]): A.query(dfn[u]);
        }
        for (auto &[id, u, d] : qs[i]) if (d) B.upd(dfn[u], -d), B.upd(dfn_[u] + 1, d);
    }
    For (i, 1, m) if (op[i][0] == '?') printf("%lld\n", ans[i]);

    return 0;
}
