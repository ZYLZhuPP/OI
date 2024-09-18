#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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
	inline bool operator ~ () { return ~c; }
} io;

int n, q, fa[N], rt[N], val[N], sz[N], ans[N];
vector<int > pt[N], T[N];
vector<array<int, 2 > > qs[N];

namespace Tire {
    int tot, rub[N * 30], top;
    array<int, 2 > ch[N * 30];
    inline int ne() { return top? rub[top--]: ++tot; }
    inline void add(int u, int x) {
        rFor (i, 29, 0) {
            int c = x >> i & 1;
            if (!ch[u][c]) ch[u][c] = ne();
            u = ch[u][c];
        }
    }
    inline int query(int u, int x) {
        int res = 0;
        rFor (i, 29, 0) {
            int c = x >> i & 1;
            if (ch[u][!c]) res |= 1 << i, u = ch[u][!c];
            else u = ch[u][c];
        }
        return res;
    }
    inline void del(int &u) { if (u) rub[++top] = u, del(ch[u][0]), del(ch[u][1]), u = 0; }
}
using namespace Tire;

inline void ins(int u, int v) {
    pt[u].pb(v);
    add(rt[u], val[v]);
}

inline void solve(int u) {
    sz[u] = 1;
    int son = 0;
    for (auto &v : T[u]) {
        solve(v); sz[u] += sz[v];
        if (sz[v] > sz[son]) son = v;
    }
    if (!son) rt[u] = ne();
    else rt[u] = rt[son], swap(pt[u], pt[son]);
    for (auto &v : T[u]) if (v ^ son) {
        del(rt[v]);
        for (auto &x : pt[v]) ins(u, x);
        pt[v].resize(0);
    }
    ins(u, u);
    for (auto &[x, id] : qs[u]) ans[id] = query(rt[u], x);
}

int main() {
    while (~(io >> n >> q)) {
        tot = top = 0;
        For (i, 1, n) io >> val[i], rt[i] = 0;
        For (i, 2, n) io >> fa[i], T[fa[i]].pb(i);
        int u, x;
        For (i, 1, q) io >> u >> x, qs[u].pb({x, i});
        solve(1);
        For (i, 1, q) printf("%d\n", ans[i]);
        pt[1].resize(0);
        For (i, 1, n) T[i].resize(0), qs[i].resize(0);
        For (i, 1, tot) ch[i][0] = ch[i][1] = 0;
    }

    return 0;
}
