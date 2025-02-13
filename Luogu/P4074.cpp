#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); i++)
#define rFor(i, r, l) for (int i = (r); i >= (l); i--)
#define pb push_back
typedef long long ll;
const int N = 1e5 + 5;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, q, S, B;
int fa[N][18], dep[N], be[N], stk[N], top;
int val[N], w[N], cnt[N], c[N], on[N], op[N], x[N], y[N], z[N];
ll ans[N], Ans;
vector<int > T[N];

struct OP {
    int x, y, t;
    bool operator < (const OP &a) const { return be[x]^be[a.x]? be[x]<be[a.x]: be[y]^be[a.y]? be[y]<be[a.y]: t<a.t; }
};
vector<OP > ops;

inline int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 17, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    rFor (i, 17, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

void dfs(int u, int pre) {
    int t = top;
    fa[u][0] = pre; dep[u] = dep[pre] + 1;
    For (i, 1, 17) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &v : T[u]) if (v ^ pre) {
        dfs(v, u);
        if (top - t >= S) {
            B++;
            while (top > t) be[stk[top--]] = B;
        }
    }
    stk[++top] = u;
}

void init() {
    S = pow(n, 0.66);
    dfs(1, 0);
    if (top) { B++; while (top) be[stk[top--]] = B; }
}

inline void rev(int u) {
    int co = c[u];
    if (on[u]) Ans -= 1ll * val[co] * w[cnt[co]--];
    else Ans += 1ll * val[co] * w[++cnt[co]];
    on[u] ^= 1;
}

inline void go(int t) {
    if (op[t]) return;
    int u = x[t];
    if (on[u]) rev(u), c[u] = y[t], rev(u);
    else c[u] = y[t];
}

inline void back(int t) {
    if (op[t]) return;
    int u = x[t];
    if (on[u]) rev(u), c[u] = z[t], rev(u);
    else c[u] = z[t];
}

inline void upd(int u, int v) {
    while (u ^ v) {
        if (dep[u] < dep[v]) swap(u, v);
        rev(u); u = fa[u][0];
    }
}

int main() {
    io >> n >> m >> q;
    int u, v;
    For (i, 1, m) io >> val[i];
    For (i, 1, n) io >> w[i];
    For (i, 1, n - 1) io >> u >> v, T[u].pb(v), T[v].pb(u);
    For (i, 1, n) io >> c[i];
    For (i, 1, q) {
        io >> op[i];
        if (op[i] == 0) io >> x[i] >> y[i], z[i] = c[x[i]], c[x[i]] = y[i];
        else if (op[i] == 1) {
            io >> x[i] >> y[i];
            ops.pb({x[i], y[i], i});
        }
    }
    init();
    sort(ops.begin(), ops.end());
    u = v = 1;
    int t = q;
    for (auto &[x, y, id] : ops) {
        while (t < id) go(++t);
        while (t > id) back(t--);
        upd(u, x); upd(v, y);
        int f = lca(x, y);
        rev(f); ans[id] = Ans; rev(f);
        u = x; v = y;
    }
    For (i, 1, q) if (op[i] == 1) printf("%lld\n", ans[i]);

    return 0;
}
