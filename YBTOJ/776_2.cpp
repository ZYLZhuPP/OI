#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e5 + 5;

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

int n, m, q, rt[N];
vector<int > es[N];

namespace Seg {
    int tot;
    struct Node {
        int l, r, sz;
        Node() { l = r = sz = 0; }
    } o[N * 60];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline int copy(const int &p) { o[++tot] = o[p]; return tot; }
    inline void upd(int &p, int l, int r, const int &x) {
        if (l > x || r < x) return;
        p = copy(p); o[p].sz++;
        if (l == r) return;
        M; upd(goL, x); upd(goR, x);
    }
    inline int query(int p, int l, int r, int q, const int &x, const int &y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return o[q].sz - o[p].sz;
        M; return query(goL, o[q].l, x, y) + query(goR, o[q].r, x, y);
    }
}

namespace KR1 {
    int pa[N], tot, dfn[N], dfn_[N], tim, fa[N][20];
    vector<int > T[N];
    inline int find(int u) { return pa[u]^u? pa[u] = find(pa[u]): u; }
    void dfs(int u, int pre) {
        dfn[u] = ++tim;
        For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto &v : T[u]) dfs(v, u);
        dfn_[u] = tim;
    }
    void build() {
        For (i, 1, n) pa[i] = i;
        For (u, 1, n) {
            for (auto &v : es[u]) if (v < u) {
                int fv = find(v);
                if (fv ^ u) fa[fv][0] = pa[fv] = u, T[u].pb(fv);
            }
        }
        rFor (i, n, 1) if (!dfn[i]) dfs(i, 0);
    }
    int jump(int u, int x) {
        rFor (i, 19, 0) if (fa[u][i] && fa[u][i] <= x) u = fa[u][i];
        return u;
    }
}

namespace KR2 {
    int pa[N], tot, dfn[N], dfn_[N], tim, fa[N][20];
    vector<int > T[N];
    inline int find(int u) { return pa[u]^u? pa[u] = find(pa[u]): u; }
    void dfs(int u, int pre) {
        dfn[u] = ++tim;
        Seg::upd(rt[tim] = rt[tim - 1], 1, n, KR1::dfn[u]);
        For (i, 1, 19) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto &v : T[u]) dfs(v, u);
        dfn_[u] = tim;
    }
    void build() {
        For (i, 1, n) pa[i] = i;
        rFor (u, n, 1) {
            for (auto &v : es[u]) if (v > u) {
                int fv = find(v);
                if (fv ^ u) fa[fv][0] = pa[fv] = u, T[u].pb(fv);
            }
        }
        For (i, 1, n) if (!dfn[i]) dfs(i, 0);
    }
    int jump(int u, int x) {
        rFor (i, 19, 0) if (fa[u][i] >= x) u = fa[u][i];
        return u;
    }
}

vector<int > check_validity(int N, vector<int > X, vector<int > Y, vector<int > S, vector<int > E, vector<int > L, vector<int > R) {
    vector<int > ans;
    n = N; m = X.size(); q = S.size();
    For (i, 0, m - 1) es[X[i] + 1].pb(Y[i] + 1), es[Y[i] + 1].pb(X[i] + 1);
    KR1::build(); KR2::build();
    For (i, 0, q - 1) {
        int u = S[i] + 1, v = E[i] + 1, l = L[i] + 1, r = R[i] + 1;
        u = KR2::jump(u, l); v = KR1::jump(v, r);
        ans.pb(Seg::query(rt[KR2::dfn[u] - 1], 1, n, rt[KR2::dfn_[u]], KR1::dfn[v], KR1::dfn_[v]) > 0);
    }
    return ans;
}

int main() {
    vector<int > X, Y, S, E, L, R, ans;
    io >> n >> m >> q;
    int u, v, l, r;
    For (i, 1, m) io >> u >> v, X.pb(u), Y.pb(v);
    For (i, 1, q) io >> u >> v >> l >> r, S.pb(u), E.pb(v), L.pb(l), R.pb(r);
    ans = check_validity(n, X, Y, S, E, L, R);
    for (auto &x : ans) cout << x << endl;

    return 0;
}
