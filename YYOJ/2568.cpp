#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 40, M = 10, S = 1 << 19, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
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

int n, m, K, mi[M][N], mk[N], id[N], pt[N], f[S], no[S], s[S], ok[S], ans = 1;
ll g[N];
vector<int > D[N];
vector<array<int, 2 > > G[M][N];

inline int solve(int k) {
    For (i, 1, n) mk[i] = id[i] = -1, D[i].resize(0);
    For (u, 1, n) for (auto &[v, w] : G[k][u]) {
        if (u == v) {
            if (~mk[u] && mk[u] ^ w) return 0;
            mk[u] = w; continue;
        }
        if (w > mi[k][v]) {
            if (~mk[u] && mk[u] ^ w) return 0;
            mk[u] = w;
        }
        if (mi[k][u] == w && mi[k][v] == w) D[u].pb(v);
    }
    For (i, 1, n) if (mk[i] > mi[k][i]) return 0;
    int tot = 0;
    For (u, 1, n) if (mi[k][u] < 1e9 && !~mk[u]) pt[++tot] = u, id[u] = tot;
    For (i, 1, tot) {
        int u = pt[i]; g[i] = 0;
        for (auto &v : D[u]) if (~id[v]) g[i] |= 1ll << (id[v] - 1);
    }
    memset(s, 0, sizeof s);
    int mid = tot / 2, A = 1 << (tot - mid), B = 1 << mid;
    ok[0] = f[0] = s[0] = 1;
    For (i, 1, A - 1) {
        ok[i] = no[i] = 0;
        if (ok[i & (i - 1)]) {
            int v = __builtin_ctz(i & -i) + 1 + mid;
            f[i] = ml(f[i & (i - 1)], mi[k][pt[v]]);
            ok[i] = !(g[v] >> mid & i);
            no[i] = no[i & (i - 1)] | (g[v] & (B - 1));
        }
        if (ok[i]) add(s[no[i]], f[i]);
    }
    For (i, 0, mid - 1) For (j, 0, B - 1) if (j >> i & 1) add(s[j], s[j ^ (1 << i)]);
    int res = 0;
    For (i, 0, B - 1) {
        ok[i] = f[i] = 0;
        if (!i) ok[i] = 1, f[i] = 1;
        else if (ok[i & (i - 1)]) {
            int v = __builtin_ctz(i & -i) + 1;
            f[i] = ml(f[i & (i - 1)], mi[k][pt[v]]);
            ok[i] = !(g[v] & i);
        }
        if (ok[i]) add(res, ml(f[i], s[(B - 1) ^ i]));
    }
    return res;
}

int main() {
    io >> n >> m >> K;
    memset(mi, 63, sizeof mi);
    int u, v, w;
    For (i, 1, m) {
        io >> u >> v;
        For (j, 1, K) io >> w, G[j][u].pb({v, w}), G[j][v].pb({u, w}), cmin(mi[j][u], w), cmin(mi[j][v], w);
    }
    For (i, 1, K) mul(ans, solve(i));
    if (!ans) return puts("0"), 0;
    For (i, 1, n) if (G[1][i].empty()) return puts("-1"), 0;
    printf("%d", ans);

    return 0;
}
