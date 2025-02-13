#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mkp make_pair
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

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

int n, Q, w[N];
int dep[N], len[N], son[N], fa[N][20], val[N][20];
int h[N], t[N], tim, q[N];
ll s[N], ans[N];
vector<int > es[N];
vector<pair<int, int > > qs[N];

void dfs0(int u) {
    for (auto &v : es[u]) {
        dep[v] = dep[u] + 1;
        dfs0(v);
        if (len[v] > len[son[u]]) son[u] = v;
    }
    len[u] = len[son[u]] + 1;
}

inline void ins(int u, int x) {
    while (h[u] <= t[u] && w[x] >= w[q[h[u]]]) h[u]++;
    if (h[u] > t[u] || dep[x] < dep[q[h[u]]]) {
        q[--h[u]] = x;
        s[h[u]] = h[u]<t[u]? s[h[u] + 1] + 1ll * dep[q[h[u] + 1]] * (w[q[h[u] + 1]] - w[x]): 0;
    }
}

int p[N], T;
inline void merge(int u, int v) {
    while (h[u] <= t[u] && dep[q[h[u]]] <= dep[q[t[v]]]) p[++T] = q[h[u]++];
    while (T && h[v] <= t[v]) ins(u, dep[p[T]]>dep[q[t[v]]]? p[T--]: q[t[v]--]);
    while (T) ins(u, p[T--]);
    while (h[v] <= t[v]) ins(u, q[t[v]--]);
}

void dfs(int u) {
    tim++;
    if (son[u]) dfs(son[u]), h[u] = h[son[u]], t[u] = t[son[u]];
    else h[u] = tim + len[u], t[u] = h[u] - 1;
    for (auto &v : es[u]) if (v ^ son[u]) dfs(v), merge(u, v);
    for (auto &[W, id] : qs[u]) {
        int l = h[u], r = t[u], res = h[u] - 1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (w[q[m]] < W) res = m, l = m + 1;
            else r = m - 1;
        }
        if (res >= h[u]) ans[id] += s[h[u]] - s[res] + 1ll * dep[q[h[u]]] * w[q[h[u]]];
        ans[id] += 1ll * dep[q[res + 1]] * (W - (res>=h[u]? w[q[res]]: 0));
        ans[id] -= 1ll * dep[u] * W;
    }
    ins(u, u);
}

int main() {
    io >> n;
    For (i, 1, n) io >> w[i];
    For (i, 2, n) {
        io >> fa[i][0]; es[fa[i][0]].pb(i);
        val[i][0] = w[fa[i][0]];
        For (j, 1, 19) fa[i][j] = fa[fa[i][j - 1]][j - 1], val[i][j] = max(val[i][j - 1], val[fa[i][j - 1]][j - 1]);
    }
    dep[1] = 1; dfs0(1);
    io >> Q;
    For (i, 1, Q) {
        int s, t;
        io >> s >> t;
        ans[i] = dep[t] - dep[s];
        int mx = 0;
        rFor (j, 19, 0) if (dep[fa[t][j]] > dep[s]) mx = max(mx, val[t][j]), t = fa[t][j];
        qs[s].pb(mkp(mx, i));
    }
    dfs(1);
    For (i, 1, Q) printf("%lld\n", ans[i]);

    return 0;
}
